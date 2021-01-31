#pragma once

#include "AST/Nodes/IntegralLiteralNode.h"
#include "AST/Types/IntegerType.h"

namespace AST
{
  class IntegerLiteralNode : public IntegralLiteralNode<IntegerType, int>
  {
    using IntegralLiteralNode<IntegerType, int>::IntegralLiteralNode;

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context& ctx ) const final
    {
      return ctx.GetIRBuilder().getInt32( GetValue() );
    }
#pragma endregion
  };
}