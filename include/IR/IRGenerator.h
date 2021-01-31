#pragma once

#include "AST/Nodes/Node.h"

namespace IR
{
  class IRGenerator
  {
  public:
    IRGenerator( std::string const& outputFile )
    {
    }
    void GenerateIR( ASTNodePtr const& root )
    {
    }

  private:
    template <typename NodeTy>
    llvm::Value* Generate( ASTNodePtr const& node );
  };
}