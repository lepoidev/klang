#pragma once

#include "KLangCommon.h"
#include "AST/Types/IntegralType.h"

class IntegerType : public IntegralType
{
#pragma region Overrides
public:
  virtual llvm::Value* GenerateIRInstFrom( ASTNodePtr const& ) const
  {
    return {};
  };
  virtual llvm::Value*
  GenerateIRInstFrom( std::vector<ASTNodePtr> const& ) const
  {
    return {};
  };
  virtual llvm::Type* GetLLVMType( IRContext const& ctx )
  {
    return {};
  };
  virtual bool const IsSameType( ASTTypePtr const& otherTy ) const
  {
    return {};
  };
  virtual bool const CanPromoteTo( ASTTypePtr const& otherTy ) const
  {
    return {};
  };
  virtual bool const CanDemoteTo( ASTTypePtr const& otherTy ) const
  {
    return {};
  };
#pragma endregion
};