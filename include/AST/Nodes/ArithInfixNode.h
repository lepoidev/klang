#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/InfixNode.h"
#include "AST/Types/Type.h"

namespace AST
{
  class ArithInfixNode : public InfixNode
  {
#pragma region Constructors / Destructors
  public:
    ArithInfixNode() = delete;
    ArithInfixNode( ASTNodePtr const& left, ASTNodePtr const& right ) :
      InfixNode { left, right }
    {
      SetType( left->GetType() );
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}