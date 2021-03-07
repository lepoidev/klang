#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/BlockNode.h"
#include "AST/Types/FunctionType.h"

namespace AST
{
  class FunctionNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    FunctionNode() = delete;
    FunctionNode( std::string const& functionName,
                  ASTTypePtr const& returnType,
                  std::vector<ASTTypePtr> const& paramTypes,
                  ASTNodePtr const& funcBody ) :
      Node {},
      m_functionName { functionName }, m_funcBody { funcBody }
    {
      SetType( CreateGenericType<FunctionType>( returnType, paramTypes ) );
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const GetFunctionName() const
    {
      return m_functionName;
    }
    auto const GetFuncType() const
    {
      return CastType<FunctionType>( GetType() );
    }
    auto const GetParamTypes() const
    {
      return GetFuncType()->GetParamTypes();
    }
    auto const GetReturnType() const
    {
      return GetFuncType()->GetReturnType();
    }
    auto const GetFuncBody() const
    {
      return m_funcBody;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const& astParamTypes { GetParamTypes() };
      std::vector<llvm::Type*> llvmParamTypes {};
      std::transform( astParamTypes.begin(),
                      astParamTypes.end(),
                      llvmParamTypes.begin(),
                      AST::CreateTypeConverter( ctx ) );

      auto const llvmReturnType { GetReturnType()->GetLLVMType( ctx ) };
      auto const llvmFunctionType { llvm::FunctionType::get(
        llvmReturnType, {}, false ) };

      auto const llvmFunction { llvm::Function::Create(
        llvmFunctionType,
        llvm::Function::ExternalLinkage,
        GetFunctionName(),
        ctx.GetModule() ) };

      auto const& entryName { GetFunctionName() + "_entry" };
      auto const entryPoint { llvm::BasicBlock::Create(
        ctx.GetGlobalLLVMContext(), entryName, llvmFunction ) };

      ctx.GetIRBuilder().SetInsertPoint( entryPoint );

      ctx.GetSymbolTable().PushNewScope();
      GetFuncBody()->GenerateIR( ctx );
      ctx.GetSymbolTable().PopScope();

      if( not( llvmFunction->getBasicBlockList().back().getTerminator() ) )
      {
        if( auto const& retTy { GetReturnType() }; retTy == nullptr )
        {
          ctx.GetIRBuilder().CreateRetVoid();
        }
        else
        {
          ctx.GetIRBuilder().CreateRet( retTy->GenerateDefaultIRInst( ctx ) );
        }
      }

      return llvmFunction;
    }
#pragma endregion

  private:
    std::string m_functionName;
    ASTNodePtr m_funcBody;
  };
}