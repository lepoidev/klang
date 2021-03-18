#pragma once

#include <KBaseVisitor.h>
#include "AST/ASTNodes.h"
#include "AST/ASTTypes.h"

namespace AST
{
  class ASTGenerator : public KBaseVisitor
  {
    antlrcpp::Any
    visitReturnStatement( KParser::ReturnStatementContext* ctx ) override
    {
      auto const hasExpr { ctx->expr() != nullptr };
      ASTNodePtr const expr {
        hasExpr ? static_cast<ASTNodePtr>( visit( ctx->expr() ) ) : nullptr
      };
      return CreateGenericNode<ReturnNode>( expr );
    }

    antlrcpp::Any visitFile( KParser::FileContext* ctx ) override
    {
      std::vector<ASTNodePtr> statements {};
      for( auto& functionDeclare : ctx->functionDeclare() )
      {
        statements.push_back(
          static_cast<ASTNodePtr>( visit( functionDeclare ) ) );
      }
      return CreateGenericNode<FileNode>( statements );
    }

    antlrcpp::Any
    visitIntegerLiteral( KParser::IntegerLiteralContext* ctx ) override
    {
      std::string const text { ctx->getText() };
      auto const val { std::stoi( text ) };
      return CreateGenericNode<IntegerLiteralNode>( val );
    }

    antlrcpp::Any
    visitFunctionDeclare( KParser::FunctionDeclareContext* ctx ) override
    {
      auto const& functionIdentifier { ctx->functionIdentifier() };
      std::string const functionName {
        functionIdentifier->functionName->getText()
      };
      std::vector<ASTTypePtr> paramTypes {};
      auto const& returnType { CreateType<IntegerType>() };
      auto const& funcBody { static_cast<ASTNodePtr>(
        visit( ctx->statement() ) ) };
      return CreateGenericNode<FunctionNode>(
        functionName, returnType, paramTypes, funcBody );
    }

    antlrcpp::Any
    visitBooleanLiteral( KParser::BooleanLiteralContext* ctx ) override
    {
      std::string const text { ctx->getText() };
      auto const val { text == "true" };
      return CreateGenericNode<BooleanLiteralNode>( val );
    }

    antlrcpp::Any
    visitBlockStatement( KParser::BlockStatementContext* ctx ) override
    {
      std::vector<ASTNodePtr> statements {};
      for( auto& statement : ctx->statement() )
      {
        statements.push_back( static_cast<ASTNodePtr>( visit( statement ) ) );
      }
      return CreateGenericNode<BlockNode>( statements );
    }

    antlrcpp::Any visitBooleanExpr( KParser::BooleanExprContext* ctx ) override
    {
      auto const left { static_cast<ASTNodePtr>( visit( ctx->left ) ) };
      auto const right { static_cast<ASTNodePtr>( visit( ctx->right ) ) };
      if( auto const& eqOp { ctx->equalityOperation() }; eqOp != nullptr )
      {
        if( eqOp->IsEqual() != nullptr )
        {
          return CreateGenericNode<EQNode>( left, right );
        }
        else if( eqOp->NotIsEqual() != nullptr )
        {
          return CreateGenericNode<NEQNode>( left, right );
        }
      }
      else if( auto const& cmpOp { ctx->comparisonOperation() };
               cmpOp != nullptr )
      {
        if( cmpOp->CloseAngle() != nullptr )
        {
          return CreateGenericNode<LTNode>( left, right );
        }
        else if( cmpOp->LessEqual() != nullptr )
        {
          return CreateGenericNode<LTENode>( left, right );
        }
        else if( cmpOp->OpenAngle() != nullptr )
        {
          return CreateGenericNode<GTNode>( left, right );
        }
        else if( cmpOp->GreaterEqual() != nullptr )
        {
          return CreateGenericNode<GTENode>( left, right );
        }
      }
      return visitChildren( ctx );
    }

    antlrcpp::Any visitConditionalStatement(
      KParser::ConditionalStatementContext* ctx ) override
    {
      auto const condExpr { static_cast<ASTNodePtr>(
        visit( ctx->condition()->expr() ) ) };
      auto const thenStatement { static_cast<ASTNodePtr>(
        visit( ctx->statement().at( 0 ) ) ) };
      ASTNodePtr const elseStatement { ctx->statement().size() > 1 ?
                                         static_cast<ASTNodePtr>(
                                           visit( ctx->statement().at( 1 ) ) ) :
                                         nullptr };
      return CreateGenericNode<CondNode>(
        condExpr, thenStatement, elseStatement );
    }

    antlrcpp::Any visitAssertExpr( KParser::AssertExprContext* ctx ) override
    {
      auto const exprNode { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
      auto const expr { ctx->expr()->getText() };
      auto const line { ctx->getStart()->getLine() };
      auto const file { "file" };
      return CreateGenericNode<AssertNode>( file, expr, line, exprNode );
    }

    antlrcpp::Any
    visitIdentifierExpr( KParser::IdentifierExprContext* ctx ) override
    {
      std::string const identifier { ctx->Identifier()->getText() };
      return CreateGenericNode<IdentifierNode>( identifier );
    }

    antlrcpp::Any visitAutoDecl( KParser::AutoDeclContext* ctx ) override
    {
      std::string const identifier { ctx->Identifier()->getText() };
      auto const isMutable { ctx->Mut() != nullptr };
      auto const& exprNode { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
      auto declType { exprNode->GetType()->Clone() };
      declType->SetMut( isMutable );
      return CreateGenericNode<DeclNode>( identifier, declType, exprNode );
    }
  };
}