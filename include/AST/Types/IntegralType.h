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
    llvm::Value*
    GenerateStackAllocation( IR::Context const& ctx,
                             std::string const& name ) const override
    {
      return ctx.GetIRBuilder().CreateAlloca( GetLLVMType( ctx ), {}, name );
    }
#pragma endregion
  };
}