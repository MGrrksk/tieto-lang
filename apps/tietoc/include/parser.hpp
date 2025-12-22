#pragma once
#include <lexer.hpp>
#include <common/poolalloc.hpp>
#include <common/errors.hpp>
#include <expr.hpp>

// Tool responsible for parsing tokenized source code into AST (Abstract Syntax Tree).
class Parser {
    // Reference to a lexical analysis module providing tokens.
    Lexer* lexer;
    // Reference to a bump allocator for AST nodes.
    PoolAllocator* pool;
    // Previous token.
    Token prevT;
    // Next token.
    Token nextT;
    // Current error code.
    ErrorCode errorCode;
    // Helper function moving to the next token in the sequence and returning reference to it.
    Token& next();
    // Helper method returning information on whether the next token is one of the given types. Moves to the next one if true.
    bool nextIs(std::initializer_list<TokenType> types);
    // Helper function ensuring if the next token is of given type. Moves to the next one if it is, enters error mode with given code if not.
    void expected(TokenType token, ErrorCode code);
    // Helper function entering error mode for the given code and logging error message for it.
    void error(ErrorCode code);

    // Method parsing a single expression.
    Expr* expression();
    // Method parsing an equality expression (`A == B`, `A != B`).
    Expr* equalityExpr();
    // Method parsing a comparison expression (`A > B`, `A >= B`, `A < B`, `A <= B`).
    Expr* comparisonExpr();
    // Method parsing a term expression (`A + B`, `A - B`).
    Expr* termExpr();
    // Method parsing a factor expression (`A * B`, `A / B`, `A // B`, `A % B`).
    Expr* factorExpr();
    // Method parsing an exponent expression (`A ** B`).
    Expr* exponentExpr();
    // Method parsing an unary expression (`-E`, `not E`).
    Expr* unaryExpr();
    // Method parsing a primary expression (`(E)`, literals).
    Expr* primaryExpr();
    public:
        // Constructor initializing the parser with reference to a lexical analysis module and a pool allocator.
        Parser(Lexer* lexerRef, PoolAllocator* allocatorRef);
        // This function parses source code into AST and returns it (temporarily single expression). Throws an exception if `lexer` is not configured.
        Expr* parse();
};