#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/BooleanInfixNode.h"

namespace AST
{
  class NEQNode : public BooleanInfixNode
  {
    using BooleanInfixNode::BooleanInfixNode;
#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const operandType { GetLeft()->GetType() };
      auto const res { operandType->CreateNEQ( ctx, GetLeft(), GetRight() ) };
      return res;
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}
