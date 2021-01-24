#pragma once

class IRContext
{
public:
  IRContext() {};
  llvm::LLVMContext& GetGlobalLLVMContext() const
  {
    return *m_globalLLVMContext;
  };
  llvm::IRBuilder<>& GetIRBuilder() const
  {
    return *m_irBuilder;
  };
  llvm::Module& GetModule() const
  {
    return *m_module;
  }

protected:
  llvm::LLVMContext* m_globalLLVMContext;
  llvm::IRBuilder<>* m_irBuilder;
  llvm::Module* m_module;
};