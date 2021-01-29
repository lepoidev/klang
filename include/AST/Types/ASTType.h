#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/ASTNode.h"

class ASTType
{
#pragma region IR Generation
public:
  virtual llvm::Value* GenerateIRInstFrom( ASTNodePtr const& ) const = 0;
  virtual llvm::Value*
  GenerateIRInstFrom( std::vector<ASTNodePtr> const& ) const = 0;
#pragma endregion

#pragma region Type Identification
public:
  virtual bool const IsIntegral() const = 0;
  virtual llvm::Type* GetLLVMType( IRContext const& ctx ) = 0;
  llvm::Type::TypeID const GetLLVMTypeID( IRContext const& ctx )
  {
    return GetLLVMType()->getTypeID();
  };
#pragma endregion

#pragma region Conversion
public:
  virtual bool const IsSameType( ASTTypePtr const& otherTy ) const = 0;
  virtual bool const CanPromoteTo( ASTTypePtr const& otherTy ) const = 0;
  virtual bool const CanDemoteTo( ASTTypePtr const& otherTy ) const = 0;
  bool const CanConvertTo( ASTTypePtr const& otherTy )
  {
    return IsSameType( otherTy ) || CanPromoteTo( otherTy ) ||
           CanDemoteTo( otherTy );
  };
#pragma endregion
};

using ASTTypePtr = std::shared_ptr<ASTType>;