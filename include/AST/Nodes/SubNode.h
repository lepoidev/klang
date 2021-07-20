#pragma once

#include "KLangCommon.h"
#include "ArithInfixNode.h"

namespace AST
{
  class SubNode : public ArithInfixNode
  {
#pragma region Constructors / Destructors
    using ArithInfixNode::ArithInfixNode;
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      return GetType()->CreateSub( ctx, GetLeft(), GetRight() );
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}