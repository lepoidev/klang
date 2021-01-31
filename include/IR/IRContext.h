#pragma once

class IRContext
{
#pragma region Constuctors / Destructors
public:
  IRContext() = delete;
  IRContext( llvm::LLVMContext& globalLLVMContext,
             llvm::IRBuilder<>& irBuilder,
             llvm::Module& module ) :
    m_globalLLVMContext { globalLLVMContext },
    m_irBuilder { irBuilder }, m_module { module }
  {
  }
  virtual ~IRContext() = default;
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
#pragma endregion

protected:
  llvm::LLVMContext& m_globalLLVMContext;
  llvm::IRBuilder<>& m_irBuilder;
  llvm::Module& m_module;
};