#pragma once

#include <KBaseVisitor.h>
#include "AST/Nodes/ASTNode.h"
#include "AST/Nodes/IntegerLiteralNode.h"

class ASTGenerator : public KBaseVisitor
{
  antlrcpp::Any visitFile( KParser::FileContext* ctx ) override
  {
    return ASTNodePtr {};
  }
  antlrcpp::Any
  visitIntegerLiteral( KParser::IntegerLiteralContext* ctx ) override
  {
    std::string const text { ctx->getText() };
    auto const val { std::stoi( text ) };
    return ASTNode::CreateNode<IntegerLiteralNode>( val );
  }
};