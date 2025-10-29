#pragma once

// Enum type representing every single type of token in the language.
enum TokenType {
    TT_LPAREN,      // Operator `(`
    TT_RPAREN,      // Operator `)`
    TT_LBRACK,      // Operator `[`
    TT_RBRACK,      // Operator `]`
    TT_LBRACE,      // Operator `{`
    TT_RBRACE,      // Operator `}`
    TT_COMMA,       // Operator `,`
    TT_DOT,         // Operator `.`
    TT_SEMICOLON,   // Operator `;`
    TT_COLON,       // Operator `:`
    TT_QUESTION,    // Operator `?`
    TT_PLUS,        // Operator `+`
    TT_MINUS,       // Operator `-`
    TT_STAR,        // Operator `*`
    TT_DBLSTAR,     // Operator `**`
    TT_SLASH,       // Operator `/`
    TT_DBLSLASH,    // Operator `//`
    TT_PERCENT,     // Operator `%`
    TT_DBLDOT,      // Operator `..`
    TT_DBLDOTEQ,    // Operator `..=`
    TT_EQUAL,       // Operator `=`
    TT_DBLEQUAL,    // Operator `==`
    TT_NEQUAL,      // Operator `!=`
    TT_GRATER,      // Operator `>`
    TT_GTEQUAL,     // Operator `>=`
    TT_LESS,        // Operator `<`
    TT_LTEQUAL,     // Operator `<=`
    TT_ARROW,       // Operator `=>`
    TT_STREAM,      // Operator `|>`
    TT_AND,         // Keyword `and`
    TT_OR,          // Keyword `or`
    TT_NOT,         // Keyword `not`
    TT_TRUE,        // Keyword `true`
    TT_FALSE,       // Keyword `false`
    TT_NULL,        // Keyword `null`
    TT_IF,          // Keyword `if`
    TT_ELSE,        // Keyword `else`
    TT_WHILE,       // Keyword `while`
    TT_VAR,         // Keyword `var`
    TT_CONST,       // Keyword `const`
    TT_FN,          // Keyword `fn`
    TT_RETURN,      // Keyword `return`
    TT_ID,          // Identifier
    TT_INT,         // Integer literal
    TT_FLOAT,       // Float literal
    TT_STRING,      // String literal
    TT_NEWLINE,     // Newline
    TT_ERRCHAR,     // Unrecognized character error mark
    TT_ERRSTR,      // Unterminated string error mark
    TT_EOF          // EOF mark
};

// Struct representing single input unit of source code.
struct Token {
    // Enum value representing the type of token
    TokenType type;
    // Pointer to the first character of the token in the source code.
    // Token does not own the memory of `lexeme` field, therefore its usage is valid only by the time parsing is finished. Also, string is not terminated at the token's end and usage with `length` field is required.
    // The only exception are tokens of type `TT_ERROR`, whose `lexeme` field is owned by token and does not point to the source code.
    const char* lexeme;
    // Length of the token in the source code.
    // It shall be used while accessing token's lexeme as it is not terminated.
    unsigned int length;
    // Number of line in the source code at which the token appeared.
    unsigned int line;
    // Number of column in the source code at which the token appeared. May not work well with tabulation characters as their length is unspecified.
    unsigned int column;
};