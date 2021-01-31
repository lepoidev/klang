#pragma once

#include "AST/Nodes/IntegralLiteralNode.h"
#include "AST/Types/IntegerType.h"

class IntegerLiteralNode : public IntegralLiteralNode<IntegerType, int>
{
  using IntegralLiteralNode<IntegerType, int>::IntegralLiteralNode;

public:
  llvm::Value* GenerateIR( IRContext& ctx ) const final
  {
    return ctx.GetIRBuilder().getInt32( GetValue() );
  }
};
