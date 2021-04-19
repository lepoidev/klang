#include "AST/TypeResolver.h"

namespace AST
{
  ASTTypePtr const TypeResolver::ResolveTypes( ASTNodePtr const& root )
  {
    auto const result { root->Accept( *this ) };
    if( result.has_value() )
    {
      return std::any_cast<ASTTypePtr>( result );
    }
    return {};
  }
  std::any
  TypeResolver::VisitChildrenWithScope( Node& node,
                                        ScopedVisitChildrenCB const& cb )
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
  std::any TypeResolver::Visit( IdentifierNode& node )
  {
    if( auto const symbol {
          m_symbolTable.ResolveSymbol( node.GetIdentifier() ) };
        symbol )
    {
      node.SetType( symbol->get().GetType() );
    }
    return {};
  }
  std::any TypeResolver::Visit( DeclNode& node )
  {
    VisitChildren( node );
    m_symbolTable.AddSymbol( node.GetIdentifier(), node.GetDeclType() );
    return {};
  }
  std::any TypeResolver::Visit( BlockNode& node )
  {
    return VisitChildrenWithScope( node );
  }
  std::any TypeResolver::Visit( FileNode& node )
  {
    return VisitChildrenWithScope( node );
  }
  std::any TypeResolver::Visit( FunctionNode& node )
  {
    return VisitChildrenWithScope( node );
  }
}