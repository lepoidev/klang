#pragma once

#include "KLangCommon.h"

namespace AST
{
  class Type
  {
#pragma region Constructors / Destructors
  public:
    virtual ~Type() = default;
    Type( bool const isMut = false ) : m_isMut { isMut }
    {
    }
#pragma endregion

#pragma region Type Errors
  public:
    class OperationNotSupportedError : public std::logic_error
    {
    public:
      OperationNotSupportedError() :
        std::logic_error { "Operation Not Supported" }
      {
      }
    };
#pragma endregion

#pragma region IR Generation
  public:
    virtual llvm::Value*
    GenerateDefaultIRInst( IR::Context const& ctx ) const = 0;
    virtual llvm::Value* GenerateIRInstFrom( IR::Context const& ctx,
                                             ASTNodePtr const& node ) const = 0;
    virtual llvm::Value*
    GenerateIRInstFrom( IR::Context const& ctx,
                        std::vector<ASTNodePtr> const& node ) const = 0;
#pragma endregion

    //#pragma region Printing
    //#pragma endregion

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

#pragma region Verification
  protected:
    static void
    VerifySameType( ASTNodePtr const& left, ASTNodePtr const& right )
    {
      auto const& leftType { left->GetType() };
      auto const& rightType { right->GetType() };
      assert( leftType->IsSameType( rightType ) );
    }
#pragma endregion

#pragma region Boolean Operations
  public:
    virtual std::pair<llvm::Value*, llvm::Value*>
    GenerateLR( IR::Context const& ctx,
                ASTNodePtr const& left,
                ASTNodePtr const& right ) const
    {
      VerifySameType( left, right );
      auto const leftIR { left->GenerateIR( ctx ) };
      auto const rightIR { right->GenerateIR( ctx ) };
      return { leftIR, rightIR };
    }

    template <typename FuncTy>
    llvm::Value* CreateInfixOp( IR::Context const& ctx,
                                ASTNodePtr const& left,
                                ASTNodePtr const& right,
                                FuncTy const& func ) const
    {
      auto const [leftIR, rightIR] { GenerateLR( ctx, left, right ) };
      return std::invoke( func, ctx.GetIRBuilder(), leftIR, rightIR, "" );
    }

    virtual llvm::Value* CreateEQ( IR::Context const& ctx,
                                   ASTNodePtr const& left,
                                   ASTNodePtr const& right ) const
    {
      throw OperationNotSupportedError();
    };

    virtual llvm::Value* CreateNEQ( IR::Context const& ctx,
                                    ASTNodePtr const& left,
                                    ASTNodePtr const& right ) const
    {
      throw OperationNotSupportedError();
    };

    virtual llvm::Value* CreateGT( IR::Context const& ctx,
                                   ASTNodePtr const& left,
                                   ASTNodePtr const& right ) const
    {
      throw OperationNotSupportedError();
    };

    virtual llvm::Value* CreateGTE( IR::Context const& ctx,
                                    ASTNodePtr const& left,
                                    ASTNodePtr const& right ) const
    {
      throw OperationNotSupportedError();
    };

    virtual llvm::Value* CreateLT( IR::Context const& ctx,
                                   ASTNodePtr const& left,
                                   ASTNodePtr const& right ) const
    {
      throw OperationNotSupportedError();
    };

    virtual llvm::Value* CreateLTE( IR::Context const& ctx,
                                    ASTNodePtr const& left,
                                    ASTNodePtr const& right ) const
    {
      throw OperationNotSupportedError();
    };

#pragma endregion

#pragma region Getters / Setters
  public:
    auto const IsMut() const
    {
      return m_isMut;
    }
    void SetMut( bool const isMut )
    {
      m_isMut = isMut;
    }
#pragma endregion

  private:
    bool m_isMut;
  };

#pragma region Namespace Functions
  template <typename ASTTypeTy>
  static auto CastType( ASTTypePtr const& nodePtr )
  {
    return std::dynamic_pointer_cast<ASTTypeTy>( nodePtr );
  }

  template <typename ASTTypeTy, typename... Args>
  static auto CreateType( Args&&... args )
  {
    return std::make_shared<ASTTypeTy>( std::forward<Args>( args )... );
  }

  static auto const CreateTypeConverter( IR::Context const& ctx )
  {
    return
      [&]( ASTTypePtr const& astType ) { return astType->GetLLVMType( ctx ); };
  }

  template <typename ASTTypeTy, typename... Args>
  static auto CreateGenericType( Args&&... args )
  {
    return CastType<Type>(
      std::make_shared<ASTTypeTy>( std::forward<Args>( args )... ) );
  }
#pragma endregion
}