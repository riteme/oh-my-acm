# -*- coding: utf-8 -*-

# Project Setting
DOCUMENT_TITLE = "Encyclopedia? of Algorithms"
OUTPUT_PATH = 'output.html'
IGNORES = ['test*', 'tmp/*', 'README.md', 'readme.md']

# Clang Settings
LIBCLANG_PATH = '/usr/lib/llvm-6.0/lib/libclang.so.1'
CLANG_ARGS = ['-std=c++14', '-x', 'c++']

# CSS Settings
CODE_BLOCK_CLASS = 'code-block'
LINE_CLASS = 'line'
LINE_NUMBER_CLASS = 'number'
CODE_CLASS = 'code'
TAG_BEGIN = '<span class="{name}">'
TAG_END = '</span>'
KEYWORD_CLASS = 'keyword'
IDENTIFIER_CLASS = 'ident'
COMMENT_CLASS = 'comment'
LITERAL_CLASS = 'literal'
PUNCTUATION_CLASS = 'punct'
NON_ASCII_CLASS = 'non-ascii'
SPECIAL = {
    'pod': [
        'bool', 'char', 'short', 'int', 'long', 'signed', 'unsigned',
        'float', 'double', 'void', 'wchar', 'size_t', '__int128_t',
        'char16_t', 'i16', 'i32', 'i64', 'i8', 'u16', 'u32', 'u64', 'u8'
    ],
    'preprocessor': [
        'include', 'define', 'undef', 'pragma', 'if', 'else', 'elif', 'endif',
        'ifdef', 'ifndef'
    ],
    'simple-variable': list('abcdefghlpqrstuvwxyz')
}

# Makrdown Settings
MARKDOWN_EXTENSIONS = [
    'markdown.extensions.fenced_code',
    'markdown.extensions.footnotes',
    'markdown.extensions.tables',
    'markdown.extensions.toc',
    'markdown.extensions.smart_strong',
    'markdown.extensions.attr_list',
    'markdown.extensions.nl2br',
    'markdown.extensions.meta',
    #'markdown.extensions.smarty',
    'oh-my-acm.latex',
    'oh-my-acm.tasklist',
    'oh-my-acm.delins'
]

# Metainfo Settings
META_TITLE = u'title'
META_CATEGORY = u'category'
META_DESCRIPTION = u'description'
META_RANK = u'rank'
META_DEFAULT_TITLE = u'无标题'
META_DEFAULT_CATEGORY = u'未分类'
META_DOCUMENT_DEFAULT_CATEGORY = u'其它文档'
META_DEFAULT_RANK = 0

# Filename-Generated Metainfo Settings
NAMEMETA_SEPARATER = '，'
NAMEMETA_KEYS = [META_TITLE, META_CATEGORY]

# Source File Settings
FILE_EXTENSIONS = ['.cpp', '.c', '.cxx']
DESCRIPTION_EXTENSIONS = ['.md', '.mkd', '.markdown']
ENCODING = 'utf-8'
PATH_ENCODING = 'utf-8'
TABSIZE = 2

# Display Settings
REPLACEMENT = {
    '<': '&lt;',
    '>': '&gt;',
    '&': '&amp;',
}

# Generator Settings
DISABLE_DEBUG = True
CACHE_DIRECTORY = '.cache'
DISABLE_CACHE = False
BLOCK_BEGIN_MARCO = 'ACM_BEGIN'
BLOCK_END_MARCO = 'ACM_END'

# Document Settings
CONTENT_TEMPLATE = u'<div class="toc">{toc}</div>{separator}{document}'
TOC_CATEGORY_TEMPLATE = u'<h3 id="{category_md5}"><div class="left">{category}</div><div class="right">□</div></h3>'
TOC_TITLE_TEMPLATE = u'<h4 class="title"><b><a href="#{id}">{id}</a></b>. {title}</h4>'
DOCUMENT_TEMPLATE = u'''<div class="source-code">
<h4 id="{id}"><div class="left">
<b><a href="#{category_md5}">{id}</a>.</b><div class="document-title">{title}</div>
<div class="document-path">[{path}]</div></div>
<div class="right">■</div></h4>
{description}
{code}</div>'''
UNUSED_DOCUMENT_TEMPLATE = u'''<div class="document">
<h6><div class="left">∘ <code>{title}</code></div><div class="right">■</div></h6>
<div>{description}</div></div>
'''
PAGE_SEPARATOR = u'<hr />'
WEBPAGE_TEMPLATE = u'''<!DOCTYPE html><html><head>
  <link href=".katex/katex.min.css" type="text/css" rel="stylesheet">
  <script src=".katex/katex.min.js" type="text/javascript"></script>
  <script src=".katex/contrib/auto-render.min.js" type="text/javascript"></script>
  <script>
    document.addEventListener("DOMContentLoaded", function() {{
      renderMathInElement(document.body, options = {{delimiters: [{{ left: "$$", right: "$$", display: true }}, {{ left: "$", right: "$", display: false }}]}});
    }});
  </script>
  <link rel="stylesheet" type="text/css" href="style.css">
  <title>{document_title}</title>
</head><body>
{document}
</body></html>
'''
