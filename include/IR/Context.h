#pragma once

#include "KLangCommon.h"
#include "Symbols/SymbolTable.h"
#include "IR/IRSymbol.h"

namespace IR
{
  class Context
  {
#pragma region Constuctors / Destructors
  public:
    Context() = delete;
    Context( llvm::LLVMContext& globalLLVMContext,
             llvm::IRBuilder<>& irBuilder,
             llvm::Module& module,
             IRSymbolTable& symbolTable ) :
      m_globalLLVMContext { globalLLVMContext },
      m_irBuilder { irBuilder }, m_module { module }, m_symbolTable {
        symbolTable
      }
    {
    }
    virtual ~Context() = default;
#pragma endregion

#pragma region Getters
  public:
    llvm::LLVMContext& GetGlobalLLVMContext() const
    {
      return m_globalLLVMContext;
    }
    llvm::IRBuilder<>& GetIRBuilder() const
    {
      return m_irBuilder;
    }
    llvm::Module& GetModule() const
    {
      return m_module;
    }
    IRSymbolTable& GetSymbolTable() const
    {
      return m_symbolTable;
    }
#pragma endregion

  protected:
    llvm::LLVMContext& m_globalLLVMContext;
    llvm::IRBuilder<>& m_irBuilder;
    llvm::Module& m_module;
    IRSymbolTable& m_symbolTable;
  };
}