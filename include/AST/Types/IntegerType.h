#pragma once

#include "KLangCommon.h"
#include "AST/Types/IntegralType.h"

namespace AST
{
  class IntegerType : public IntegralType
  {
#pragma region Overrides
  public:
    llvm::Value* GenerateIRInstFrom( ASTNodePtr const& node ) const override
    {
      return {};
    }
    llvm::Value*
    GenerateIRInstFrom( std::vector<ASTNodePtr> const& node ) const override
    {
      return {};
    }
    llvm::Type* GetLLVMType( IR::Context const& ctx ) override
    {
      return ctx.GetIRBuilder().getInt32Ty();
    }
    bool const IsSameType( ASTTypePtr const& otherTy ) const override
    {
      return CastType<IntegerType>( otherTy ) != nullptr;
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

#pragma region Operations
    llvm::Value* CreateEQ( IR::Context const& ctx,
                           llvm::Value* left,
                           llvm::Value* right ) const final
    {
      return ctx.GetIRBuilder().CreateICmpEQ( left, right );
    }
#pragma endregion
  };
}