#pragma once

#include "KLangCommon.h"
#include "Symbols/SymbolScope.h"

class SymbolTable
{
#pragma region Constructors / Destructors
public:
  SymbolTable() = default;
#pragma endregion

#pragma region Errors
public:
  class UndefinedSymbolError : public std::logic_error
  {
  public:
    UndefinedSymbolError() = delete;
    UndefinedSymbolError( std::string const& symbolName ) :
      std::logic_error { "Undefined Symbol \'" + symbolName + "\'" }
    {
    }
  };
  class SymbolAlreadyDefinedError : public std::logic_error
  {
  public:
    SymbolAlreadyDefinedError() = delete;
    SymbolAlreadyDefinedError( std::string const& symbolName ) :
      std::logic_error { "Symbol \'" + symbolName +
                         "\' already defined in current scope" }
    {
    }
  };
#pragma endregion

#pragma region Scope Interations
public:
  void PushNewScope()
  {
    static int scopeId { 0 };
    auto const scopeName { "scope_" + std::to_string( scopeId++ ) };
    m_scopes.push_front( { scopeName } );
  }

  void PopScope()
  {
    m_scopes.pop_front();
  }
#pragma endregion

#pragma region Symbol Management
public:
  bool IsDefinedInCurrentScope( std::string const& symbolName )
  {
    auto const firstScope { m_scopes.begin() };
    if( firstScope != m_scopes.end() )
    {
      return firstScope->HasSymbolName( symbolName );
    }
    return false;
  }
  std::optional<std::reference_wrapper<Symbol>>
  ResolveSymbol( std::string const& symbolName )
  {
    for( auto& scope : m_scopes )
    {
      if( scope.HasSymbolName( symbolName ) )
      {
        return scope.GetSymbol( symbolName );
      }
    }
    return {};
  }
#pragma endregion

private:
  std::deque<SymbolScope> m_scopes;
};