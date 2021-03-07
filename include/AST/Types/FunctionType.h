#pragma once

#include "AST/Types/Type.h"

namespace AST
{
  class FunctionType : public Type
  {
#pragma region Constructors / Destructors
  public:
    FunctionType() = delete;
    FunctionType( ASTTypePtr returnType,
                  std::vector<ASTTypePtr> paramTypes,
                  bool const isMut = false ) :
      Type { isMut },
      m_returnType { returnType }, m_paramTypes { paramTypes }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetParamTypes() const
    {
      return m_paramTypes;
    }
    auto const& GetReturnType() const
    {
      return m_returnType;
    }
#pragma endregion

#pragma region Overrides
  public:
    virtual llvm::Value*
    GenerateDefaultIRInst( IR::Context const& ctx ) const override
    {
      return ctx.GetIRBuilder().getFalse();
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
      return {};
    }
    bool const IsSameType( ASTTypePtr const& otherTy ) const override
    {
      return false;
    }
    bool const CanPromoteTo( ASTTypePtr const& otherTy ) const override
    {
      return {};
    }
    bool const CanDemoteTo( ASTTypePtr const& otherTy ) const override
    {
      return {};
    }
    bool const IsIntegral() const final
    {
      return false;
    }

#pragma endregion

  private:
    ASTTypePtr m_returnType;
    std::vector<ASTTypePtr> m_paramTypes;
  };
}