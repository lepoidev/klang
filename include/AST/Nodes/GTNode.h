#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/BooleanInfixNode.h"

namespace AST
{
  class GTNode : public BooleanInfixNode
  {
    using BooleanInfixNode::BooleanInfixNode;
#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const operandType { GetLeft()->GetType() };
      auto const res { operandType->CreateGT( ctx, GetLeft(), GetRight() ) };
      return res;
    }
#pragma endregion
  };
}