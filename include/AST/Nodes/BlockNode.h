#pragma once

#include "AST/Nodes/ASTNode.h"

class BlockNode : public ASTNode
{
public:
  BlockNode( std::vector<ASTNodePtr> const& statements ) :
    ASTNode {}, m_statments { statements }
  {
  }

protected:
  std::vector<ASTNodePtr> m_statements;
};