#pragma once

#include "KLangCommon.h"
#include "AST/Types/BooleanType.h"
#include "AST/Nodes/InfixNode.h"

namespace AST
{
  class BooleanInfixNode : public InfixNode
  {
#pragma region Constructors / Destructors
  public:
    BooleanInfixNode( ASTNodePtr const& left, ASTNodePtr const& right ) :
      InfixNode { left, right }
    {
      SetType( CreateType<BooleanType>() );
    }
#pragma endregion
  };
}