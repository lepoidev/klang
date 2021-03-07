#pragma once

#include "KLangCommon.h"
#include "AST/Types/Type.h"

namespace AST
{
  class IntegralType : public Type
  {
    using Type::Type;
#pragma region Overrides
  public:
    bool const IsIntegral() const final
    {
      return true;
    }
#pragma endregion
  };
}