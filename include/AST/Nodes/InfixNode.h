#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/ASTNode.h"

class InfixNode : public ASTNode
{
public:
  InfixNode( ASTNodePtr const& left, ASTNodePtr const& right ) :
    ASTNode {}, m_left { left }, m_right { right }
  {
  }

protected:
  ASTNodePtr m_left;
  ASTNodePtr m_right;
};