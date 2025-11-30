#pragma once
#include <token.hpp>
#include <common/value.hpp>

// Abstract base class for all AST expression node types.
class Expr;
// Interface for visitor design pattern for `Expr` class, must be implemented by everything that processes `Expr` objects.
class ExprVisitor;
// AST class for literals.
class LiteralExpr;
// AST class for unary expressions.
class UnaryExpr;
// AST class for binary expressions.
class BinaryExpr;

class Expr {
    public:
        // Virtual method for the visitor pattern, accepts `ExprVisitor`.
        virtual void accept(ExprVisitor* visitor) = 0;
        // Virtual destructor
        virtual ~Expr() = default;
};

class ExprVisitor {
    public:
        // Virtual method visiting `LiteralExpr` object.
        virtual void visitLiteralExpr(LiteralExpr* expr) = 0;
        // Virtual method visiting `UnaryExpr` object.
        virtual void visitUnaryExpr(UnaryExpr* expr) = 0;
        // Virtual method visiting `BinaryExpr` object.
        virtual void visitBinaryExpr(BinaryExpr* expr) = 0;
        // Virtual destructor
        virtual ~ExprVisitor() = default;
};

class LiteralExpr: public Expr {
    public:
        // Value represented by the literal.
        Value value;
        // Initializing constructor.
        LiteralExpr(Value litValue): value(litValue) {}
        // Method accepting visitor implementing `ExprVisitor`.
        void accept(ExprVisitor* visitor) {visitor->visitLiteralExpr(this);}
};

class UnaryExpr: public Expr {
    public:
        // Expression's operand.
        Expr* expr;
        // Expression's operator.
        TokenType oper;
        // Initializing constructor.
        UnaryExpr(Expr* innerExpr, TokenType operType): expr(innerExpr), oper(operType) {}
        // Method accepting visitor implementing `ExprVisitor`.
        void accept(ExprVisitor* visitor) {visitor->visitUnaryExpr(this);}
};

class BinaryExpr: public Expr {
    public:
        // Expression's left operand.
        Expr* left;
        // Expression's right operand.
        Expr* right;
        // Expression's operator.
        TokenType oper;
        // Initializing constructor.
        BinaryExpr(Expr* leftExpr, Expr* rightExpr, TokenType operType): left(leftExpr), right(rightExpr), oper(operType) {}
        // Method accepting visitor implementing `ExprVisitor`.
        void accept(ExprVisitor* visitor) {visitor->visitBinaryExpr(this);}
};