#pragma once

#include <KBaseVisitor.h>
#include "AST/Nodes/ASTNode.h"

class ASTGenerator : public KBaseVisitor
{
  antlrcpp::Any visitFile( KParser::FileContext* ctx ) override
  {
    return ASTNodePtr {};
  }
};