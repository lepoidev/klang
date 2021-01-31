#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class UnaryNode : public Node
  {
  public:
    UnaryNode() = delete;
    UnaryNode( ASTNodePtr const& node ) : Node {}, m_node {}
    {
    }

  protected:
    ASTNodePtr m_node;
  };
}