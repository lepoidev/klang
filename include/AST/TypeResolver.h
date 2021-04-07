#pragma once

#include "AST/Visitor/BaseVisitor.h"
#include "Symbols/SymbolTable.h"

namespace AST
{
  class TypeResolver : public BaseVisitor
  {
#pragma region Constructors / Destructors
  public:
    TypeResolver() = default;
#pragma endregion

#pragma region Type Resolving
  public:
    ASTTypePtr const ResolveTypes( ASTNodePtr const& root )
    {
      auto const result { root->Accept( *this ) };
      if( result.has_value() )
      {
        return std::any_cast<ASTTypePtr>( result );
      }
      return {};
    }
#pragma endregion

#pragma region Helpers
  private:
    using ScopedVisitChildrenCB = std::function<void()>;
    std::any
    VisitChildrenWithScope( Node& node, ScopedVisitChildrenCB const& cb = {} )
    {
      m_symbolTable.PushNewScope();
      auto const ret { VisitChildren( node ) };
      if( cb )
      {
        cb();
      }
      m_symbolTable.PopScope();

      return ret;
    }
#pragma endregion

#pragma region Overrides
  private:
    std::any Visit( IdentifierNode& node ) override
    {
      if( auto const symbol {
            m_symbolTable.ResolveSymbol( node.GetIdentifier() ) };
          symbol )
      {
        node.SetType( symbol->get().GetType() );
      }
      return {};
    }
    std::any Visit( DeclNode& node ) override
    {
      VisitChildren( node );
      m_symbolTable.AddSymbol( node.GetIdentifier(), {}, node.GetDeclType() );
      return {};
    }
    std::any Visit( BlockNode& node ) override
    {
      return VisitChildrenWithScope( node );
    }
    std::any Visit( FileNode& node ) override
    {
      return VisitChildrenWithScope( node );
    }
    std::any Visit( FunctionNode& node ) override
    {
      return VisitChildrenWithScope( node );
    }
#pragma endregion

  private:
    SymbolTable m_symbolTable;
  };
}
