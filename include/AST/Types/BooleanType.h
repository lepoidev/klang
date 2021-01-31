#pragma once

#include "KLangCommon.h"
#include "AST/Types/IntegralType.h"

namespace AST
{
  class BooleanType : public IntegralType
  {
#pragma region Overrides
  public:
    llvm::Value* GenerateIRInstFrom( ASTNodePtr const& ) const override
    {
      return {};
    }
    llvm::Value*
    GenerateIRInstFrom( std::vector<ASTNodePtr> const& ) const override
    {
      return {};
    }
    llvm::Type* GetLLVMType( IR::Context const& ctx ) override
    {
      return {};
    }
    bool const IsSameType( ASTTypePtr const& otherTy ) const override
    {
      return {};
    }
    bool const CanPromoteTo( ASTTypePtr const& otherTy ) const override
    {
      return {};
    }
    bool const CanDemoteTo( ASTTypePtr const& otherTy ) const override
    {
      return {};
    }
#pragma endregion
  };
}