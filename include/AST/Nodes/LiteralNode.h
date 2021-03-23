#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class LiteralNode : public Node
  {
#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}