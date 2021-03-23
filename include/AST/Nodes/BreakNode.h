#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class BreakNode : public Node
  {
#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion
  };
}