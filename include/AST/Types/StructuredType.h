#pragma once

#include "KLangCommon.h"
#include "AST/Types/ASTType.h"

class StructuredType : public ASTType
{
public:
  bool const IsIntegral() final
  {
    return false;
  }
};