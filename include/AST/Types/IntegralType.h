#pragma once

#include "KLangCommon.h"
#include "AST/Types/ASTType.h"

class IntegralType : public ASTType
{
public:
  bool const IsIntegral() final
  {
    return true;
  }
};