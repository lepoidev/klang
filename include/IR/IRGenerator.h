#pragma once

#include "AST/Nodes/ASTNode.h"

class IRGenerator
{
public:
  IRGenerator( std::string const& outputFile ) {};
  void GenerateIR( std::shared_ptr<ASTNode> const& root ) {};

private:
  template <typename NodeTy>
  llvm::Value* Generate( std::shared_ptr<NodeTy> const& node );
};