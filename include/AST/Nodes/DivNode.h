#pragma once

#include "KLangCommon.h"
#include "ArithInfixNode.h"

namespace AST
{
  class DivNode : public ArithInfixNode
  {
#pragma region Constructors / Destructors
    using ArithInfixNode::ArithInfixNode;
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      return GetType()->CreateDiv( ctx, GetLeft(), GetRight() );
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}