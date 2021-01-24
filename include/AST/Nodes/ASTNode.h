#pragma once

#include "IR/IRContext.h"

class ASTNode
{
public:
  virtual ~ASTNode() {};
  virtual llvm::Value* GenerateIR( IRContext const& ctx ) = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;