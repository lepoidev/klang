#pragma once

#include "KLangCommon.h"
#include "Symbols/SymbolTable.h"

namespace IR
{
  class IRSymbol : public Symbol
  {
#pragma region Constructors / Destructors
  public:
    IRSymbol() = delete;
    IRSymbol( std::string const& name,
              ASTTypePtr const& type,
              llvm::Value* ptr ) :
      Symbol { name, type },
      m_ptr { ptr }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const GetPtr() const
    {
      return m_ptr;
    }
#pragma endregion

  private:
    llvm::Value* m_ptr;
  };

  using IRSymbolTable = SymbolTable<IRSymbol>;
}