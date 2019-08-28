#!/usr/bin/python
# -*- coding: utf-8 -*-

__VERSION__ = 'v0.1'

import os
import os.path
import sys
import re
import argparse
import hashlib
import importlib

import itertools
zip = itertools.izip

try:
    import cPickle as pickle
except:
    import pickle

from sys import argv
from colorama import Fore
from collections import defaultdict, namedtuple

config = None

def md5(x):
    if type(x) is unicode:
        x = x.encode('utf-8')
    return hashlib.md5(x).hexdigest()

# Logging
def INFO(message):
    print '%s(info)%s %s' % (Fore.GREEN, Fore.RESET, message)
def WARN(message):
    print '%s(warn)%s %s' % (Fore.YELLOW, Fore.RESET, message)
def ERROR(message):
    print '%s(error)%s %s' % (Fore.RED, Fore.RESET, message)
def DEBUG(message):
    if not config.DISABLE_DEBUG:
        print '%s(debug)%s %s' % (Fore.BLUE, Fore.RESET, message)

# Ignores
def ignored(path):
    def _matched(m, s):
        r = m.match(s)
        return r and r.end() == len(s)
    basename = os.path.basename(path)
    DEBUG('IGN: %s, %s' % (path, basename))
    for m in config.IGNORES:
        if _matched(m, basename) or _matched(m, path):
            return True
    return False

# Cache Management
def load_cache(content):
    key = md5(content)
    if not os.path.exists(config.CACHE_DIRECTORY):
        os.makedirs(config.CACHE_DIRECTORY)
    path = os.path.join(config.CACHE_DIRECTORY, key)
    return (path, False if config.DISABLE_CACHE else os.path.exists(path))

# Python Markdown
import markdown, re
import markdown.extensions.codehilite
from markdown import Extension
from markdown.inlinepatterns import \
    LinkPattern, ReferencePattern, AutolinkPattern, AutomailPattern, \
    LINK_RE, REFERENCE_RE, SHORT_REF_RE, AUTOLINK_RE, AUTOMAIL_RE
from markdown.inlinepatterns import SimpleTagPattern
from markdown.postprocessors import Postprocessor

# LaTeX Extension
# on-my-acm.latex
class MathJaxPattern(markdown.inlinepatterns.Pattern):
    def __init__(self):
        markdown.inlinepatterns.Pattern.__init__(
            self,
            r'(?<!\\)(\$\$?)(.+?)\2'
        )

    def handleMatch(self, m):
        node = markdown.util.etree.Element('tex')
        node.text = markdown.util.AtomicString(
            m.group(2) + m.group(3) + m.group(2))
        return node


class MathJaxExtension(markdown.Extension):
    def extendMarkdown(self, md, md_globals):
        md.inlinePatterns.add('tex', MathJaxPattern(), '<escape')

def markdown_latex(configs=[]):
    return MathJaxExtension(configs)

# Tasklist Extension
# oh-my-acm.tasklist
class ChecklistExtension(Extension):
    def extendMarkdown(self, md, md_globals):
        md.postprocessors.add('checklist', ChecklistPostprocessor(md),
                              '>raw_html')

class ChecklistPostprocessor(Postprocessor):
    pattern = re.compile(r'<li>\[([ Xx])\]')

    def run(self, html):
        html = re.sub(self.pattern, self._convert_checkbox, html)
        before = '<ul>\n<li><input type="checkbox"'
        after = before.replace('<ul>', '<ul class="checklist">')
        return html.replace(before, after)

    def _convert_checkbox(self, match):
        state = match.group(1)
        checked = ' checked' if state != ' ' else ''
        return '<li><input type="checkbox" disabled%s>' % checked

def markdown_tasklist(configs=None):
    if configs is None:
        return ChecklistExtension()
    else:
        return ChecklistExtension(configs=configs)

# DelIns Extension
# oh-my-acm.delins
class DelInsExtension(markdown.extensions.Extension):
    def extendMarkdown(self, md, md_globals):
        DEL_RE = r"(\~\~)(.+?)(\~\~)"
        INS_RE = r"(\+\+)(.+?)(\+\+)"
        md.inlinePatterns.add(
            'del', SimpleTagPattern(DEL_RE, 'del'), '<not_strong')
        md.inlinePatterns.add(
            'ins', SimpleTagPattern(INS_RE, 'ins'), '<not_strong')

def markdown_delins(configs={}):
    return DelInsExtension(configs=dict(configs))

# Initialize Markdown & C++ Parser according to preferences
md = None
clang = None
cl = None
def initialize_parsers():
    global md
    global clang
    global cl

    INFO('Loading Python Markdown...')
    for i in xrange(len(config.MARKDOWN_EXTENSIONS)):
        ext = config.MARKDOWN_EXTENSIONS[i]
        if type(ext) == str and ext.startswith('oh-my-acm'):
            ext = ext.split('.', 1)[1]
            config.MARKDOWN_EXTENSIONS[i] = eval('markdown_%s()' % ext)
    md = markdown.Markdown(extensions=config.MARKDOWN_EXTENSIONS)

    # Clang
    import clang.cindex
    INFO('Loading libclang ["%s"]...' % config.LIBCLANG_PATH)
    clang.cindex.Config.set_library_file(config.LIBCLANG_PATH)
    cl = clang.cindex.Index.create()

    INFO('Loading C++ Parser...')
    config.SPECIAL_MAP = {}
    for key, li in config.SPECIAL.items():
        for value in li:
            config.SPECIAL_MAP[value] = key

# C++ Parser
def get_tag(token):
    NONE = -1
    NON_ASCII = 1
    ASCII = 0
    def get_type(c):
        if ord(c) > 255:
            return NON_ASCII
        return ASCII

    tags = (token.spelling or token.displayname).decode('utf-8').split('\n')
    for i in xrange(len(tags)):
        last = NONE
        ret = []
        for c in tags[i]:
            t = get_type(c)
            if t != last:
                if t == NON_ASCII:
                    ret.append(config.TAG_BEGIN.format(name=config.NON_ASCII_CLASS))
                elif last != NONE:
                    ret.append(config.TAG_END)
            if c in config.REPLACEMENT:
                ret.append(config.REPLACEMENT[c])
            else:
                ret.append(c)
            last = t
        if last == NON_ASCII:
            ret.append(config.TAG_END)
        tags[i] = ''.join(ret)

    return tags

def parse_cxx(path):
    SEVERITY_NAME = {
        clang.cindex.Diagnostic.Ignored: 'IGN',
        clang.cindex.Diagnostic.Note: 'NOTE',
        clang.cindex.Diagnostic.Warning: Fore.YELLOW + 'WARN' + Fore.RESET,
        clang.cindex.Diagnostic.Error: Fore.RED + 'ERROR' + Fore.RESET,
        clang.cindex.Diagnostic.Fatal: Fore.RED + 'FATAL' + Fore.RESET
    }

    INFO('Parsing "%s"...' % path)
    DEBUG('Options: %s' % ' '.join(config.CLANG_ARGS))
    with open(path, 'r') as reader:
        content = reader.read()
        lines = content.split('\n')

    cache, flag = load_cache(content)
    if flag:
        DEBUG('"%s" cached.' % path)
        with open(cache, 'r') as reader:
            return pickle.load(reader)

    tu = cl.parse(
        path, config.CLANG_ARGS,
        options=clang.cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD
    )
    diag = list(tu.diagnostics)
    if len(diag):
        for msg in diag:
            WARN('[%s][%s: %s:%s] %s' % (
                SEVERITY_NAME[msg.severity],
                msg.location.file, msg.location.line, msg.location.column,
                msg.spelling
            ))
        WARN('Diagnostics ignored. Processing will continue.')

    DEBUG('Generating HTML code...')
    line = 1
    column = 1
    buf = []
    for token in tu.get_tokens(extent=tu.cursor.extent):
        loc = token.location
        while loc.line != line:
            # Sometimes clang will ignore line breaks "\" at the end of each line
            # trailing spaces trimmed
            buf.append(lines[line - 1][column - 1:].rstrip() + '\n')
            line += 1
            column = 1
        if loc.column != column:
            tab_count = lines[line - 1][column - 1 : loc.column - 1].count('\t')
            length = loc.column - column
            buf.append(' ' * ((length - tab_count) + tab_count * config.TABSIZE))
            column = loc.column

        tags = get_tag(token)
        #DEBUG(tags)
        classes = []
        if token.kind == clang.cindex.TokenKind.KEYWORD:
            classes.append(config.KEYWORD_CLASS)
        if token.kind == clang.cindex.TokenKind.IDENTIFIER:
            classes.append(config.IDENTIFIER_CLASS)
        if token.kind == clang.cindex.TokenKind.COMMENT:
            classes.append(config.COMMENT_CLASS)
        if token.kind == clang.cindex.TokenKind.LITERAL:
            classes.append(config.LITERAL_CLASS)
        if token.kind == clang.cindex.TokenKind.PUNCTUATION:
            classes.append(config.PUNCTUATION_CLASS)
        if len(tags) == 1 and tags[0] in config.SPECIAL_MAP:
            classes.append(config.SPECIAL_MAP[tags[0]])

        for i in xrange(len(tags)):
            tags[i] = '%s%s%s' % (
                config.TAG_BEGIN.format(name=' '.join(classes)),
                tags[i], config.TAG_END
            )
        buf.append('\n'.join(tags))

        line = token.extent.end.line
        column = token.extent.end.column
    # Includes tailing contents
    if column != len(lines[line - 1]):
        buf.append(lines[line - 1][column - 1:].rstrip())

    DEBUG('Parsing metainfo...')
    data = list(itertools.islice(tu.get_tokens(extent=tu.cursor.extent), 1))[0]
    meta = {}
    meta_end = 1
    if data.kind == clang.cindex.TokenKind.COMMENT and data.spelling.startswith('/**'):
        meta_end = data.extent.end.line + 1
        data = data.spelling.split('\n')[1:-1]
        for row in data:
            key, value = row.split(':', 1)
            key = key.strip('\* ')
            value = value.strip()
            meta[key] = value.decode(config.ENCODING)
    DEBUG('Parsing file name...')
    name = os.path.basename(os.path.splitext(path)[0])
    vals = name.split(config.NAMEMETA_SEPARATER)
    for key, val in zip(config.NAMEMETA_KEYS, vals):
        if key not in meta:
            meta[key] = val.strip().decode(config.ENCODING)
    # Default to match title with description file
    if config.META_DESCRIPTION not in meta:
        title = meta[config.META_TITLE]
        for ext in config.DESCRIPTION_EXTENSIONS:
            desc = title + ext
            DEBUG('Try "%s"...' % desc)
            if os.path.isfile(desc):
                break
            else:
                desc = None
        if desc is not None:
            meta[config.META_DESCRIPTION] = desc

    DEBUG('Generating slices...')
    last = 0
    slices = []
    for cur in tu.cursor.get_children():
        pos = cur.location.line
        if cur.kind == clang.cindex.CursorKind.MACRO_DEFINITION:
            if cur.spelling == config.BLOCK_BEGIN_MARCO:
                if last:
                    WARN('[L%s] Duplicated block beginning. Ignored.' % pos)
                else:
                    last = pos + 1
            elif cur.spelling == config.BLOCK_END_MARCO:
                if last:
                    slices.append((last, pos))
                    last = 0
                else:
                    WARN('[L%s] Unmatched block ending. Ignored.' % pos)
    if last:
        WARN('[L%s] Unmatched block beginning. Default to file end [L%s].' % (last, line))
        slices.append((last, line + 1))
    if len(slices) == 0:
        DEBUG('No specific range. Default is the entire file.')
        slices = [(meta_end, line + 1)]

    result = (''.join(buf), meta, slices)
    with open(cache, 'w') as writer:
        pickle.dump(result, writer)
    return result

def add_line_numbers(s, slices):
    data = ['<div class="%s"><div class="%s">%%s</div><div class="%s">%s</div></div>' %
        (config.LINE_CLASS, config.LINE_NUMBER_CLASS, config.CODE_CLASS, code.replace('%', '%%'))
        for code in s.split('\n')]
    output = []
    line = 0
    for l, r in slices:
        for i in xrange(l - 1, r - 1):
            line += 1
            output.append(data[i] % line)

    return ('<div class="%s">' % config.CODE_BLOCK_CLASS) + '\n'.join(output) + '</div>'

# Markdown Parser
def parse_markdown(path):
    DEBUG('Parsing markdown file: %s' % path)
    with open(path, 'r') as reader:
        content = reader.read()
    cache, flag = load_cache(content)
    if flag:
        DEBUG('"%s" cached.' % path)
        with open(cache, 'r') as reader:
            return pickle.load(reader)
    result = md.convert(content.decode(config.ENCODING))
    with open(cache, 'w') as writer:
        pickle.dump(result, writer)
    return result

# Resolver
def resolve(path, relpath):
    code, meta, slices = parse_cxx(path)

    DEBUG('Metainfo:')
    for item in meta.items():
        DEBUG('"%s": "%s"' % item)

    # Describing one document
    code = add_line_numbers(code, slices)
    desc = parse_markdown(meta[config.META_DESCRIPTION]) if config.META_DESCRIPTION in meta else ''
    title = meta[config.META_TITLE] if config.META_TITLE in meta else config.META_DEFAULT_TITLE
    category = meta[config.META_CATEGORY] if config.META_CATEGORY in meta else config.META_DEFAULT_CATEGORY
    rank = int(meta[config.META_RANK]) if config.META_RANK in meta else config.META_DEFAULT_RANK
    return namedtuple(
        'Item', ['desc', 'code', 'title', 'category', 'rank', 'path', 'meta']
    )(desc, code, title, category, rank, relpath, meta)

# Main
def main():
    global config

    parser = argparse.ArgumentParser(description='(docmeld %s) A generic document compiler for ICPC-related contests. Used by Fudan U2 in 2019 fall' % __VERSION__)
    parser.add_argument('path', help='Path to the root directory of documents or [git repo].')
    parser.add_argument('-o', '--output', help='Location for the generated HTML file.')
    parser.add_argument('-n', '--no-cache', action='store_true', help='Disable cache and force full re-generation.')
    parser.add_argument('-v', '--verbose', action='store_true', help='Show more messages.')
    parser.add_argument('-q', '--quiet', action='store_true', help='Show less messages.')
    args = parser.parse_args()

    if not os.path.isdir(args.path):
        ERROR('Failed to open directory "%s"' % args.path)
        exit(1)

    sys.path.append(os.path.abspath(args.path))
    try:
        config = importlib.import_module('preferences')
    except ImportError:
        ERROR('No preference file was found. Please ensure that there is a "preferences.py" in your project directory.')
        exit(2)

    # Compile ignorement rules
    for i in xrange(len(config.IGNORES)):
        config.IGNORES[i] = re.compile(config.IGNORES[i])

    if args.output:
        if 'OUTPUT_PATH' in dir(config) and type(config.OUTPUT_PATH) is str:
            WARN('"OUTPUT_PATH" has been specified in preferences, which will be ignored.')
        config.OUTPUT_PATH = args.output

    if args.no_cache:
        config.DISABLE_CACHE = True
    if args.verbose:
        config.DISABLE_DEBUG = False
    if args.quiet:
        config.DISABLE_DEBUG = True
    if args.verbose and args.quiet:
        WARN('Both "-q" and "-v" are enabled. Default to be quiet.')

    initialize_parsers()

    database = defaultdict(list)
    used_documents = set()
    curdir = os.getcwd()
    basedir = os.path.join(curdir, args.path)
    def search_for_sources(arg, dirname, fnames):
        fnames[:] = [x for x in fnames if not x.startswith('.')]  # Skip hidden files & folders
        os.chdir(dirname)
        cwd = os.getcwd()
        for name in fnames:
            if not os.path.isfile(name):
                continue
            base, ext = os.path.splitext(name)
            if ext in config.FILE_EXTENSIONS:
                path = os.path.abspath(os.path.join(cwd, name))
                rpath = os.path.relpath(path, start=basedir).decode(config.PATH_ENCODING)
                if not ignored(rpath):
                    result = resolve(name, rpath)
                    meta = result.meta
                    if config.META_DESCRIPTION in meta:
                        used_documents.add(
                            os.path.abspath(os.path.join(cwd, meta[config.META_DESCRIPTION])).encode(config.ENCODING)
                        )
                    database[result.category].append(result)
        os.chdir(curdir)
    os.path.walk(args.path, search_for_sources, None)

    INFO('Combining into one document...')
    cnt = 0
    toc = []
    body = []
    for category, docs in database.items():
        DEBUG('Processing category "%s"...' % category)
        toc.append(config.TOC_CATEGORY_TEMPLATE.format(category=category, category_md5=md5(category)))
        for doc in sorted(docs, key=lambda doc: (doc.rank, doc.title)):
            cnt += 1
            toc.append(config.TOC_TITLE_TEMPLATE.format(id=cnt, title=doc.title))
            body.append(config.DOCUMENT_TEMPLATE.format(
                id=cnt, title=doc.title, category=doc.category, category_md5=md5(doc.category),
                path=doc.path, description=doc.desc, code=doc.code))

    toc.append(config.TOC_CATEGORY_TEMPLATE.format(
        category=config.META_DOCUMENT_DEFAULT_CATEGORY,
        category_md5=md5(config.META_DOCUMENT_DEFAULT_CATEGORY)))
    body.append(config.PAGE_SEPARATOR)
    def search_for_documents(arg, dirname, fnames):
        fnames[:] = [x for x in fnames if not x.startswith('.')]  # Skip hidden files & folders
        os.chdir(dirname)
        cwd = os.getcwd()
        for name in fnames:
            if not os.path.isfile(name):
                continue
            base, ext = os.path.splitext(name)
            if ext in config.DESCRIPTION_EXTENSIONS:
                path = os.path.abspath(os.path.join(cwd, name))
                rpath = os.path.relpath(path, start=basedir).decode(config.PATH_ENCODING)
                if not ignored(rpath) and path not in used_documents:
                    body.append(config.UNUSED_DOCUMENT_TEMPLATE.format(
                        title=rpath, description=parse_markdown(path)))
        os.chdir(curdir)
    os.path.walk(args.path, search_for_documents, None)

    output_file = os.path.join(args.path, config.OUTPUT_PATH)
    DEBUG('Writing into "%s"...' % output_file)
    with open(output_file, 'w') as writer:
        data = config.WEBPAGE_TEMPLATE.format(
            document_title=config.DOCUMENT_TITLE,
            document=config.CONTENT_TEMPLATE.format(
                toc='\n'.join(toc),
                separator=config.PAGE_SEPARATOR,
                document='\n'.join(body))
        )
        writer.write(data.encode(config.ENCODING))

if __name__ == "__main__":
    main()
