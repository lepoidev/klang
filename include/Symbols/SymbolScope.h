#pragma once

#include "KLangCommon.h"
#include "Symbols/Symbol.h"

class SymbolScope
{
#pragma region Constructors / Destructors
public:
  SymbolScope() = delete;
  SymbolScope( std::string const& scopeName ) : m_scopeName { scopeName }
  {
  }
#pragma endregion

#pragma region Symbol Management
public:
  auto const HasSymbolName( std::string const& symbolName ) const
  {
    return m_symbols.find( symbolName ) != m_symbols.end();
  }

  std::optional<std::reference_wrapper<Symbol>>
  GetSymbol( std::string const& symbolName )
  {
    if( HasSymbolName( symbolName ) )
    {
      return m_symbols.at( symbolName );
    }
    return {};
  }

  bool const AddSymbol( std::string const& symbolName,
                        llvm::Value* val,
                        ASTTypePtr const& astType )
  {
    if( HasSymbolName( symbolName ) )
    {
      return false;
    }
    m_symbols.insert( { symbolName, { symbolName, val, astType } } );
    return true;
  }
#pragma endregion

private:
  std::string m_scopeName;
  std::unordered_map<std::string, Symbol> m_symbols;
};