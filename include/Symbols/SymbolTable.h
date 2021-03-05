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
  class UndefinedSymbolError : public std::logic_error
  {
  public:
    UndefinedSymbolError() = delete;
    UndefinedSymbolError( std::string const& symbolName ) :
      std::logic_error { "Undefined Symbol \'" + symbolName + "\'" }
    {
    }
  };
#pragma endregion

#pragma region Scope Interations
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