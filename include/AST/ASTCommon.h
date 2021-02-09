#pragma once
#include <memory>

namespace AST
{
  class Node;
  class Type;
}

using ASTNodePtr = std::shared_ptr<AST::Node>;
using ASTTypePtr = std::shared_ptr<AST::Type>;
