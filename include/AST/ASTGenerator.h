#pragma once

#include <KBaseVisitor.h>
#include "AST/Nodes/Node.h"
#include "AST/Nodes/IntegerLiteralNode.h"

namespace AST
{
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
      return CreateNode<IntegerLiteralNode>( val );
    }
  };
}