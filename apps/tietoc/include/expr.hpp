#pragma once
#include <token.hpp>
#include <common/value.hpp>

// Abstract base class for all AST expression node types. 
class Expr {
    public:
        // Result data type of the expression.
        DataType type;
        // Virtual method for the visitor pattern, accepts `ExprVisitor`.
        virtual void accept(ExprVisitor* visitor) = 0;
};

// Interface for visitor design pattern for `Expr` class, must be implemented by everything that processes `Expr` objects.
class ExprVisitor {
    public:
        // Virtual method visiting `LiteralExpr` object.
        virtual void visitLiteralExpr(LiteralExpr* expr) = 0;
        // Virtual method visiting `UnaryExpr` object.
        virtual void visitUnaryExpr(UnaryExpr* expr) = 0;
        // Virtual method visiting `BinaryExpr` object.
        virtual void visitBinaryExpr(BinaryExpr* expr) = 0;
};

// AST class for literals.
class LiteralExpr: Expr {
    public:
        // Value represented by the literal.
        Value value;
        void accept(ExprVisitor* visitor) {visitor->visitLiteralExpr(this);}
};

// AST class for unary expressions.
class UnaryExpr: Expr {
    public:
        // Expression's operand.
        Expr* expr;
        // Expression's operator.
        TokenType oper;
        void accept(ExprVisitor* visitor) {visitor->visitUnaryExpr(this);}
};

// AST class for binary expressions.
class BinaryExpr: Expr {
    public:
        // Expression's left operand.
        Expr* left;
        // Expression's right operand.
        Expr* right;
        // Expression's operator.
        TokenType oper;
        void accept(ExprVisitor* visitor) {visitor->visitBinaryExpr(this);}
};