#pragma once

#include "KLangCommon.h"
#include "AST/Types/IntegralType.h"

namespace AST
{
  class IntegerType : public IntegralType
  {
    using IntegralType::IntegralType;
#pragma region Overrides
  public:
    virtual llvm::Value*
    GenerateDefaultIRInst( IR::Context const& ctx ) const override
    {
      return ctx.GetIRBuilder().getInt32( 0 );
    }
    llvm::Value* GenerateIRInstFrom( IR::Context const& ctx,
                                     ASTNodePtr const& node ) const override
    {
      return {};
    }
    llvm::Value*
    GenerateIRInstFrom( IR::Context const& ctx,
                        std::vector<ASTNodePtr> const& node ) const override
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
  public:
    llvm::Value* CreateEQ( IR::Context const& ctx,
                           ASTNodePtr const& left,
                           ASTNodePtr const& right ) const final
    {
      return CreateInfixOp(
        ctx, left, right, &llvm::IRBuilder<>::CreateICmpEQ );
    }

    llvm::Value* CreateNEQ( IR::Context const& ctx,
                            ASTNodePtr const& left,
                            ASTNodePtr const& right ) const final
    {
      return CreateInfixOp(
        ctx, left, right, &llvm::IRBuilder<>::CreateICmpNE );
    }

    llvm::Value* CreateGT( IR::Context const& ctx,
                           ASTNodePtr const& left,
                           ASTNodePtr const& right ) const final
    {
      return CreateInfixOp(
        ctx, left, right, &llvm::IRBuilder<>::CreateICmpSGT );
    };

    llvm::Value* CreateGTE( IR::Context const& ctx,
                            ASTNodePtr const& left,
                            ASTNodePtr const& right ) const final
    {
      return CreateInfixOp(
        ctx, left, right, &llvm::IRBuilder<>::CreateICmpSGE );
    };

    llvm::Value* CreateLT( IR::Context const& ctx,
                           ASTNodePtr const& left,
                           ASTNodePtr const& right ) const final
    {
      return CreateInfixOp(
        ctx, left, right, &llvm::IRBuilder<>::CreateICmpSLT );
    };

    llvm::Value* CreateLTE( IR::Context const& ctx,
                            ASTNodePtr const& left,
                            ASTNodePtr const& right ) const final
    {
      return CreateInfixOp(
        ctx, left, right, &llvm::IRBuilder<>::CreateICmpSLE );
    };
#pragma endregion
  };
}