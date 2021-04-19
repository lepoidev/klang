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
    ASTTypePtr const ResolveTypes( ASTNodePtr const& root );
#pragma endregion

#pragma region Helpers
  private:
    using ScopedVisitChildrenCB = std::function<void()>;
    std::any
    VisitChildrenWithScope( Node& node, ScopedVisitChildrenCB const& cb = {} );
#pragma endregion

#pragma region Overrides
  private:
    std::any Visit( IdentifierNode& node ) override;
    std::any Visit( DeclNode& node ) override;
    std::any Visit( BlockNode& node ) override;
    std::any Visit( FileNode& node ) override;
    std::any Visit( FunctionNode& node ) override;
#pragma endregion

  private:
    SymbolTable<Symbol> m_symbolTable;
  };
}
