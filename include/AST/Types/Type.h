#pragma once

#include "KLangCommon.h"

namespace AST
{
  class Type
  {
#pragma region Constructors / Destructors
  public:
    virtual ~Type() = default;
#pragma endregion

#pragma region IR Generation
  public:
    virtual llvm::Value* GenerateIRInstFrom( ASTNodePtr const& ) const = 0;
    virtual llvm::Value*
    GenerateIRInstFrom( std::vector<ASTNodePtr> const& ) const = 0;
#pragma endregion

#pragma region Type Identification
  public:
    virtual bool const IsIntegral() const = 0;
    virtual llvm::Type* GetLLVMType( IR::Context const& ctx ) = 0;
    llvm::Type::TypeID const GetLLVMTypeID( IR::Context const& ctx )
    {
      return GetLLVMType( ctx )->getTypeID();
    }
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
    }
#pragma endregion
  };

#pragma region Namespace Functions
  template <typename ASTTypeTy, typename... Args>
  auto CreateType( Args&&... args )
  {
    return std::make_shared<ASTTypeTy>( std::forward<Args>( args )... );
  }
#pragma endregion
}