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
    m_irBuilder { irBuilder }, m_module { module } {};
  virtual ~IRContext() = default;
#pragma endregion

#pragma region Getters
  llvm::LLVMContext& GetGlobalLLVMContext()
  {
    return m_globalLLVMContext;
  };
  llvm::IRBuilder<>& GetIRBuilder()
  {
    return m_irBuilder;
  };
  llvm::Module& GetModule()
  {
    return m_module;
  };
#pragma endregion

protected:
  llvm::LLVMContext& m_globalLLVMContext;
  llvm::IRBuilder<>& m_irBuilder;
  llvm::Module& m_module;
};