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
    UnaryNode( ASTNodePtr const& node ) : Node {}, m_node { node }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  protected:
    auto const& GetNode() const
    {
      return m_node;
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
    std::vector<ASTNodePtr> GetChildren() const override
    {
      return { GetNode() };
    }
#pragma endregion

  private:
    ASTNodePtr m_node;
  };
}