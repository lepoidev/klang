#pragma once

#include <KBaseVisitor.h>

#include "KLangCommon.h"

namespace AST
{
  class ASTGenerator : public KBaseVisitor
  {
    antlrcpp::Any visitFile( KParser::FileContext* ctx ) override;

    antlrcpp::Any
    visitFunctionDeclare( KParser::FunctionDeclareContext* ctx ) override;

#pragma region Literals
    antlrcpp::Any
    visitIntegerLiteral( KParser::IntegerLiteralContext* ctx ) override;

    antlrcpp::Any
    visitBooleanLiteral( KParser::BooleanLiteralContext* ctx ) override;
#pragma endregion

#pragma region Statements
    antlrcpp::Any visitFunctionCallStatement(
      KParser::FunctionCallStatementContext* ctx ) override;

    antlrcpp::Any
    visitReturnStatement( KParser::ReturnStatementContext* ctx ) override;

    antlrcpp::Any
    visitBlockStatement( KParser::BlockStatementContext* ctx ) override;

    antlrcpp::Any visitConditionalStatement(
      KParser::ConditionalStatementContext* ctx ) override;

    antlrcpp::Any visitWhileLoop( KParser::WhileLoopContext* ctx ) override;
#pragma endregion

#pragma region Expr
    antlrcpp::Any visitBooleanExpr( KParser::BooleanExprContext* ctx ) override;

    antlrcpp::Any
    visitNonBooleanExpr( KParser::NonBooleanExprContext* ctx ) override;
#pragma endregion

#pragma region Built In
    antlrcpp::Any visitAssertExpr( KParser::AssertExprContext* ctx ) override;
#pragma endregion

    antlrcpp::Any
    visitIdentifierExpr( KParser::IdentifierExprContext* ctx ) override;

    antlrcpp::Any visitCondition( KParser::ConditionContext* ctx ) override;

#pragma region Declaration
    antlrcpp::Any visitAutoDecl( KParser::AutoDeclContext* ctx ) override;

    antlrcpp::Any
    visitEmptyInitDecl( KParser::EmptyInitDeclContext* ctx ) override;

    antlrcpp::Any visitInitDecl( KParser::InitDeclContext* ctx ) override;
#pragma endregion

#pragma region Assignment
    antlrcpp::Any visitBasicAssign( KParser::BasicAssignContext* ctx ) override;
#pragma endregion

#pragma region Types
    antlrcpp::Any
    visitPrimitiveType( KParser::PrimitiveTypeContext* ctx ) override;

    antlrcpp::Any visitType( KParser::TypeContext* ctx ) override;
#pragma endregion

#pragma region Helpers
  private:
    template <typename CtxTy>
    std::pair<ASTNodePtr, ASTNodePtr> VisitLR( CtxTy* ctx )
    {
      auto const left { static_cast<ASTNodePtr>( visit( ctx->left ) ) };
      auto const right { static_cast<ASTNodePtr>( visit( ctx->right ) ) };
      return { left, right };
    }
#pragma endregion
  };
}