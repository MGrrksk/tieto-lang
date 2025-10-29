#pragma once
#include <token.hpp>

// Tool responsible for tokenization of source code.
// Tokens are lazily evaluated during parsing process and their `lexeme` field is valid only in this time.
class Lexer {
    // Pointer to string with source code. `nullptr` value marks lexer as not configured for tokenization.
    const char* src = nullptr;
    // Field pointing to the first character of the current token.
    const char* start = nullptr;
    // Field pointing to the currently analysed character in the sequence.
    const char* curr = nullptr;
    // Number of line in the source code at which current token starts.
    unsigned int line = 1;
    // Number of column in the source code at which current token starts. Does not account for the tabulation mark's length and assumes it is equal to one.
    unsigned int column = 1;
    // Function skipping all whitespace characters (`\n` is not considered whitespace).
    void skipWhitespace();
    // Helper function moving to the next character and returning previous one.
    char next();
    // This function returns information on whether the current character in the source is the given one. Moves to the next character if true.
    bool nextIs(char c);
    // Helper function returning token with given type and other fields computed.
    Token token(TokenType type);
    // Flag method returning information on whether the lexer has reached end of file. Sets `src` to `nullptr` when true.
    bool isEOF();
    public:
        // This method configures lexer for tokenization. It should be always called before tokenizing the code. Throws an exception when already configured.
        void configure(const char* source);
        // This method yields next token from the source code. Throws an exception when lexer is not configured.
        Token nextToken();
        // Flag method returning information on whether the lexer is during tokenization.
        bool isTokenizing();
};