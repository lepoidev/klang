#pragma once

#include <KBaseVisitor.h>

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
#pragma endregion

    antlrcpp::Any visitBooleanExpr( KParser::BooleanExprContext* ctx ) override;

#pragma region Built In
    antlrcpp::Any visitAssertExpr( KParser::AssertExprContext* ctx ) override;
#pragma endregion

    antlrcpp::Any
    visitIdentifierExpr( KParser::IdentifierExprContext* ctx ) override;

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
  };
}