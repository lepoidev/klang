#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class BlockNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    BlockNode() = delete;
    BlockNode( std::vector<ASTNodePtr> const& statements ) :
      Node {}, m_statments { statements }
    {
    }
#pragma endregion

  protected:
    std::vector<ASTNodePtr> m_statements;
  };
}