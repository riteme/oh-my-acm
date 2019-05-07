# -*- coding: utf-8 -*-

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
        'char16_t'
    ],
    'preprocessor': [
        'include', 'define', 'undef', 'pragma', 'if', 'else', 'elif', 'endif',
        'ifdef', 'ifndef'
    ]
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
META_DEFAULT_TITLE = u'无标题'
META_DEFAULT_CATEGORY = u'未分类'
META_DOCUMENT_DEFAULT_CATEGORY = u'其它文档'
META_DEFAULT_RANGE_START = 6

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
BLOCK_BEGIN_MARCO = 'ACM_BEGIN'
BLOCK_END_MARCO = 'ACM_END'

# Document Settings
CONTENT_TEMPLATE = u'{toc}{separator}{document}'
TOC_CATEGORY_TEMPLATE = u'<h3>{category}</h3>'
TOC_TITLE_TEMPLATE = u'<h4 class="title"><b>{id}</b>. {title}</h4>'
DOCUMENT_TEMPLATE = u'''<div class="source-code"><h4><b>{id}.</b> {title}</h4>
{description}
{code}</div>'''
UNUSED_DOCUMENT_TEMPLATE = u'''<div class="document"><h6>∘ <code>{title}</code></h6>
<div>{description}</div></div>
'''
PAGE_SEPARATOR = u'<hr />'
WEBPAGE_TEMPLATE = u'''<!DOCTYPE html><html><head>
  <link href="katex/katex.min.css" type="text/css" rel="stylesheet">
  <script src="katex/katex.min.js" type="text/javascript"></script>
  <script src="katex/contrib/auto-render.min.js" type="text/javascript"></script>
  <script>
    document.addEventListener("DOMContentLoaded", function() {{
      renderMathInElement(document.body, options = {{delimiters: [{{ left: "$$", right: "$$", display: true }}, {{ left: "$", right: "$", display: false }}]}});
    }});
  </script>
  <link rel="stylesheet" type="text/css" href="style.css">
</head><body>
{document}
</body></html>
'''
