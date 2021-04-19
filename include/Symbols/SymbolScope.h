#pragma once

#include "KLangCommon.h"
#include "Symbols/Symbol.h"

template <typename SymbolTy>
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

  std::optional<std::reference_wrapper<SymbolTy>>
  GetSymbol( std::string const& symbolName )
  {
    if( HasSymbolName( symbolName ) )
    {
      return m_symbols.at( symbolName );
    }
    return {};
  }

  template <typename... AdditionalArgs>
  bool const
  AddSymbol( std::string const& symbolName, AdditionalArgs&&... additionalArgs )
  {
    if( HasSymbolName( symbolName ) )
    {
      return false;
    }
    m_symbols.insert(
      { symbolName,
        { symbolName, std::forward<AdditionalArgs>( additionalArgs )... } } );
    return true;
  }
#pragma endregion

private:
  std::string m_scopeName;
  std::unordered_map<std::string, SymbolTy> m_symbols;
};