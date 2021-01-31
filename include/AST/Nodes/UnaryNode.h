#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class UnaryNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    UnaryNode() = delete;
    UnaryNode( ASTNodePtr const& node ) : Node {}, m_node {}
    {
    }
#pragma endregion

  protected:
    ASTNodePtr m_node;
  };
}