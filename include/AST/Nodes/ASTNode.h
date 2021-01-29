#pragma once

#include "KLangCommon.h"
#include "IR/IRContext.h"

class ASTNode
{
public:
  virtual ~ASTNode() {};
  virtual llvm::Value* GenerateIR( IRContext const& ctx ) const = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

template <typename NodeTy>
auto ASTNodeCast( ASTNodePtr const& nodePtr )
{
  return std::dynamic_pointer_cast<NodeTy>( nodePtr );
}