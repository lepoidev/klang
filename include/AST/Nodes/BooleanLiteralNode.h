#pragma once

#include "AST/Nodes/Intermediates/IntegralLiteralNode.h"
#include "AST/Types/BooleanType.h"

namespace AST
{
  class BooleanLiteralNode : public IntegralLiteralNode<BooleanType, bool>
  {
    using IntegralLiteralNode<BooleanType, bool>::IntegralLiteralNode;

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const val { GetValue() };
      return val ? ctx.GetIRBuilder().getTrue() : ctx.GetIRBuilder().getFalse();
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}