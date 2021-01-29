#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/ASTNode.h"

class UnaryNode : public ASTNode
{
public:
  UnaryNode( ASTNodePtr const& node ) : ASTNode {}, m_node {}
  {
  }

protected:
  ASTNodePtr m_node;

private:
  UnaryNode();
};