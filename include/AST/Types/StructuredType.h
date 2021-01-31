#pragma once

#include "KLangCommon.h"
#include "AST/Types/Type.h"

namespace AST
{
  class StructuredType : public Type
  {
  public:
    bool const IsIntegral() final
    {
      return false;
    }
  };
}