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

# Source File Settings
ENCODING = 'utf-8'
TAGSIZE = 4

# DISPLAY Settings
REPLACEMENT = {
    '<': '&lt;',
    '>': '&gt;',
    '&': '&amp;',
}

# Generator Settings
DISABLE_DEBUG = False
