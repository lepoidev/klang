#pragma once

#include "AST/Nodes/Intermediates/IntegralLiteralNode.h"
#include "AST/Types/IntegerType.h"

namespace AST
{
  class IntegerLiteralNode : public IntegralLiteralNode<IntegerType, int>
  {
    using IntegralLiteralNode<IntegerType, int>::IntegralLiteralNode;

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const val { GetValue() };
      return ctx.GetIRBuilder().getInt32( val );
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}