#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class InfixNode : public Node
  {
  public:
    InfixNode() = delete;
    InfixNode( ASTNodePtr const& left, ASTNodePtr const& right ) :
      Node {}, m_left { left }, m_right { right }
    {
    }

  protected:
    ASTNodePtr m_left;
    ASTNodePtr m_right;
  };
}