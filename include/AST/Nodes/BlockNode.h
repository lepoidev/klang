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
      Node {}, m_statements { statements }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto& GetStatements()
    {
      return m_statements;
    }
#pragma endregion

  private:
    std::vector<ASTNodePtr> m_statements;
  };
}