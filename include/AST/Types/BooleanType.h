#pragma once

#include "KLangCommon.h"
#include "AST/Types/IntegralType.h"

namespace AST
{
  class BooleanType : public IntegralType
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
      return ctx.GetIRBuilder().getInt8Ty();
    }
    bool const IsSameType( ASTTypePtr const& otherTy ) const override
    {
      return CastType<BooleanType>( otherTy ) != nullptr;
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
                           ASTNodePtr const& left,
                           ASTNodePtr const& right ) const final
    {
      VerifySameType( left, right );
      auto const leftIR { left->GenerateIR( ctx ) };
      auto const rightIR { right->GenerateIR( ctx ) };
      return ctx.GetIRBuilder().CreateICmpEQ( leftIR, rightIR );
    }
#pragma endregion
  };
}