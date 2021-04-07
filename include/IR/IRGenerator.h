#pragma once

#include <filesystem>
#include <fstream>

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"
#include "IR/Context.h"
#include "AST/TypeResolver.h"

namespace IR
{
  class IRGenerator
  {
#pragma region Constructors / Destructors
  public:
    IRGenerator() = delete;
    IRGenerator( std::string const& outputFile ) : m_outputFile { outputFile }
    {
      std::filesystem::path path { m_outputFile };
      m_moduleName = path.stem();
    }
#pragma endregion

#pragma region IR Generation
  public:
    void GenerateIR( ASTNodePtr const& root )
    {
      AST::TypeResolver typeResolver {};
      typeResolver.ResolveTypes( root );

      SymbolTable symbolTable;
      llvm::LLVMContext globalLLVMContext {};
      llvm::IRBuilder<> irBuilder { globalLLVMContext };
      llvm::Module mod { m_moduleName, globalLLVMContext };
      Context ctx { globalLLVMContext, irBuilder, mod, symbolTable };

      root->GenerateIR( ctx );

      std::ofstream out { m_outputFile };
      llvm::raw_os_ostream ros { out };
      llvm::raw_os_ostream llErr { std::cerr };
      llvm::verifyModule( mod, &llErr );
      mod.print( ros, nullptr );
    }
#pragma endregion

  private:
    std::string m_outputFile;
    std::string m_moduleName;
  };
}