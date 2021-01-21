#pragma once

#include "AST/Nodes/ASTNode.h"
#include "AST/ASTVisitor.h"

class IRGenerator : public ASTVisitor
{
public:
  IRGenerator( std::string const& outputFile ) {};
  void Generate( std::shared_ptr<ASTNode> root ) {};
};