#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/BlockNode.h"

namespace AST
{
  class FunctionNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    FunctionNode() = delete;
    FunctionNode( std::string const& functionName,
                  std::vector<ASTTypePtr> const& paramTypes,
                  ASTTypePtr const& returnType,
                  ASTNodePtr const& funcBody ) :
      Node {},
      m_functionName { functionName }, m_paramTypes { paramTypes },
      m_returnType { returnType }, m_funcBody { funcBody }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const GetFunctionName() const
    {
      return m_functionName;
    }
    auto const GetParamTypes() const
    {
      return m_paramTypes;
    }
    auto const GetReturnType() const
    {
      return m_returnType;
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

      // llvmFunction->getBasicBlockList()
      //  .push_back()

      ctx.GetIRBuilder().SetInsertPoint( entryPoint );

      GetFuncBody()->GenerateIR( ctx );

      return llvmFunction;
    }
#pragma endregion

  private:
    std::string m_functionName;
    std::vector<ASTTypePtr> m_paramTypes;
    ASTTypePtr m_returnType;
    ASTNodePtr m_funcBody;
  };
}