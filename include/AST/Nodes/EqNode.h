#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/BooleanInfixNode.h"

namespace AST
{
  class EqNode : public BooleanInfixNode
  {
#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const& leftType { GetLeft()->GetType() };
      auto const& rightType { GetRight()->GetType() };
      assert( leftType->IsSameType( rightType ) );

      auto const left { GetLeft()->GenerateIR( ctx ) };
      auto const right { GetRight()->GenerateIR( ctx ) };

      auto const res { leftType->CreateEQ( ctx, left, right ) };
      return res;
    }
#pragma endregion
  };
}