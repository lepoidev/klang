#pragma once

#include "AST/Nodes/IntegralLiteralNode.h"
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
      return ctx.GetIRBuilder().getInt8( GetValue() );
    }
#pragma endregion
  };
}