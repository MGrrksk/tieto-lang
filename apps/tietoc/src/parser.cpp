#include <parser.hpp>
#include <stdexcept>

#define debug(fnname) printf("%s(next: %d)\n", fnname, nextT.type)

Parser::Parser(Lexer* lexerRef, PoolAllocator* allocatorRef): lexer(lexerRef), pool(allocatorRef), errorCode(EC_NONE) {}
Expr* Parser::parse() {
    if (!lexer->isTokenizing()) throw std::runtime_error("Parser::parse(): Lexer is not configured for tokenizing. Call its `configure(source)` method first.");
    next();
    // Temporarily it's just one expression.
    return expression();
}

Expr* Parser::expression() {
    return equalityExpr();
}
Expr* Parser::equalityExpr() {
    debug("equality");
    Expr* left = comparisonExpr();
    while (nextIs({TT_EQUAL, TT_NEQUAL})) {
        TokenType oper = prevT.type;
        Expr* right = comparisonExpr();
        left = pool->alloc<BinaryExpr>(left, right, oper);
    }
    return left;
}
Expr* Parser::comparisonExpr() {
    debug("comparison");
    Expr* left = termExpr();
    while (nextIs({TT_GREATER, TT_GTEQUAL, TT_LESS, TT_LTEQUAL})) {
        TokenType oper = prevT.type;
        Expr* right = termExpr();
        left = pool->alloc<BinaryExpr>(left, right, oper);
    }
    return left;
}
Expr* Parser::termExpr() {
    debug("term");
    Expr* left = factorExpr();
    while (nextIs({TT_PLUS, TT_MINUS})) {
        TokenType oper = prevT.type;
        Expr* right = factorExpr();
        left = pool->alloc<BinaryExpr>(left, right, oper);
    }
    return left;
}
Expr* Parser::factorExpr() {
    debug("factor");
    Expr* left = exponentExpr();
    while (nextIs({TT_STAR, TT_SLASH, TT_DBLSLASH, TT_PERCENT})) {
        TokenType oper = prevT.type;
        Expr* right = exponentExpr();
        left = pool->alloc<BinaryExpr>(left, right, oper);
    }
    return left;
}
Expr* Parser::exponentExpr() {
    debug("exponent");
    Expr* left = unaryExpr();
    while (nextIs({TT_DBLSTAR})) {
        TokenType oper = prevT.type;
        Expr* right = unaryExpr();
        left = pool->alloc<BinaryExpr>(left, right, oper);
    }
    return left;
}
Expr* Parser::unaryExpr() {
    debug("unary");
    if (nextIs({TT_MINUS, TT_NOT})) {
        TokenType oper = prevT.type;
        Expr* expr = unaryExpr();
        return pool->alloc<UnaryExpr>(expr, oper);
    }
    return primaryExpr();
}
Expr* Parser::primaryExpr() {
    debug("primary");
    if (nextIs({TT_INT, TT_FLOAT, TT_STRING})) return pool->alloc<LiteralExpr>(prevT);
    if (nextIs({TT_LPAREN})) {
        Expr* expr = expression();
        expected(TT_RPAREN, EC_MISSING_RPAREN);
        return expr;
    }
    error(EC_MISSING_EXPR);
    return nullptr;
}

bool Parser::nextIs(std::initializer_list<TokenType> types) {
    for (TokenType type: types)
        if (nextT.type == type) {
            next();
            return true;
        }
    return false;
}
Token& Parser::next() {
    prevT = nextT;
    nextT = lexer->nextToken();
    return prevT;
}
void Parser::expected(TokenType token, ErrorCode code) {
    if (nextT.type == token) next();
    else error(code);
}
void Parser::error(ErrorCode code) {
    printf("Error (E%03d): %s\n", code, ERROR_MESSAGES[code]);
}