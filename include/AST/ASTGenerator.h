#pragma once

#include <KBaseVisitor.h>
#include "AST/Nodes/Node.h"
#include "AST/Nodes/IntegerLiteralNode.h"
#include "AST/Nodes/BooleanLiteralNode.h"
#include "AST/Nodes/FunctionNode.h"
#include "AST/Nodes/ReturnNode.h"
#include "AST/Nodes/FileNode.h"
#include "AST/Nodes/BlockNode.h"

namespace AST
{
  class ASTGenerator : public KBaseVisitor
  {
    antlrcpp::Any
    visitReturnStatement( KParser::ReturnStatementContext* ctx ) override
    {
      auto const hasExpr { ctx->expr() != nullptr };
      ASTNodePtr expr { hasExpr ?
                          static_cast<ASTNodePtr>( visit( ctx->expr() ) ) :
                          nullptr };
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
        functionName, paramTypes, returnType, funcBody );
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
  };
}