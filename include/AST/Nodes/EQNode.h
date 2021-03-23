#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/BooleanInfixNode.h"

namespace AST
{
  class EQNode : public BooleanInfixNode
  {
    using BooleanInfixNode::BooleanInfixNode;
#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const operandType { GetLeft()->GetType() };
      auto const res { operandType->CreateEQ( ctx, GetLeft(), GetRight() ) };
      return res;
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}
