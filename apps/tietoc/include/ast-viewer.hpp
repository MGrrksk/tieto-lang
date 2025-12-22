#pragma once
#include <expr.hpp>
#include <cstdio>

class ASTViewer: public ExprVisitor {
    int indent = 0;
    public:
        void visitLiteralExpr(LiteralExpr* expr) {
            for (int i=0;i<indent;i++) printf("  ");
            printf("Literal(%d) = %.*s\n", expr->token.type - TT_INT, expr->token.length, expr->token.lexeme);
        }
        void visitUnaryExpr(UnaryExpr* expr) {
            for (int i=0;i<indent;i++) printf("  ");
            printf("Unary(%d):\n", expr->oper);
            indent++;
            expr->expr->accept(this);
            indent--;
        }
        void visitBinaryExpr(BinaryExpr* expr) {
            for (int i=0;i<indent;i++) printf("  ");
            printf("Binary(%d):\n", expr->oper);
            indent++;
            expr->left->accept(this);
            expr->right->accept(this);
            indent--;
        }
};