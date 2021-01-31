#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class InfixNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    InfixNode() = delete;
    InfixNode( ASTNodePtr const& left, ASTNodePtr const& right ) :
      Node {}, m_left { left }, m_right { right }
    {
    }
#pragma endregion

  protected:
    ASTNodePtr m_left;
    ASTNodePtr m_right;
  };
}