#!/usr/bin/env python

import preferences as config
import argparse

from sys import argv
from colorama import Fore

def INFO(message):
    print(Fore.GREEN + "(info) " + Fore.RESET + message)
def WARN(message):
    print(Fore.YELLOW + "(warn) " + Fore.RESET + message)
def ERROR(message):
    print(Fore.RED + "(error) " + Fore.RESET + message)
def DEBUG(message):
    if not config.DISABLE_DEBUG:
        print(Fore.BLUE + "(debug) " + Fore.RESET + message)

import clang.cindex
INFO('Loading libclang ["%s"]...' % config.LIBCLANG_PATH)
clang.cindex.Config.set_library_file(config.LIBCLANG_PATH)
cl = clang.cindex.Index.create()

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

def parse(path):
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
        evil = reader.read()
        angle = evil.replace('\t', ' ' * config.TAGSIZE)

    if evil != angle:
        DEBUG('Replacing tabs...')
        with open(path, 'w') as writer:
            writer.write(angle)
    tu = cl.parse(path, config.CLANG_ARGS)
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
        if loc.line != line:
            buf.append('\n' * (loc.line - line))
            line = loc.line
            column = 1
        if loc.column != column:
            buf.append(' ' * (loc.column - column))
            column = loc.column

        tags = get_tag(token)
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

    return ''.join(buf)

def add_line_numbers(s):
    output = ''.join((
        '<div class="%s"><div class="%s">%s</div><div class="%s">%s</div></div>' %
        (config.LINE_CLASS, config.LINE_NUMBER_CLASS, idx, config.CODE_CLASS, code)
        for idx, code in enumerate(s.split('\n'), 1)))
    return ('<div class="%s">' % config.CODE_BLOCK_CLASS) + output + '</div>'

def main():
    config.SPECIAL_MAP = {}
    for key, li in config.SPECIAL.items():
        for value in li:
            config.SPECIAL_MAP[value] = key

    parser = argparse.ArgumentParser()
    parser.add_argument('path')
    parser.add_argument('-o', '--output', required=True)
    parser.add_argument('-q', '--quiet', action='store_true')
    args = parser.parse_args()

    if args.quiet:
        config.DISABLE_DEBUG = True

    data = add_line_numbers(parse(args.path))
    DEBUG('Writing into "%s"...' % args.output)
    with open(args.output, 'w') as writer:
        writer.write(
            ('<html><head><link rel="stylesheet" type="text/css" href="style.css"></head><body>' +
            data + '</body></html>').encode(config.ENCODING)
        )

if __name__ != "__main__":
    ERROR('Not a python module.')
else:
    main()
