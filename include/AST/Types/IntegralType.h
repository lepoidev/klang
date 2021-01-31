#pragma once

#include "KLangCommon.h"
#include "AST/Types/Type.h"

namespace AST
{
  class IntegralType : public Type
  {
  public:
    bool const IsIntegral() const final
    {
      return true;
    }
  };
}