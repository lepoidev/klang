#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"
#include "AST/Types/Type.h"

namespace AST
{
  class AssignNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    AssignNode( std::string const& identifier, ASTNodePtr const& exprNode ) :
      Node {}, m_identifier { identifier }, m_exprNode { exprNode }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetIdentifier() const
    {
      return m_identifier;
    }
    auto const& GetExprNode() const
    {
      return m_exprNode;
    }
    auto const HasExpr() const
    {
      return m_exprNode != nullptr;
    }
#pragma endregion

#pragma region IR Generation
  protected:
    auto const GenerateNewValue( IR::Context const& ctx,
                                 ASTTypePtr const& targetType ) const
    {
      if( HasExpr() )
      {
        return GetExprNode()->GenerateIR( ctx );
      }
      return targetType->GenerateDefaultIRInst( ctx );
    }

  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const result { ctx.GetSymbolTable().ResolveSymbol(
        GetIdentifier() ) };
      if( !result )
      {
        throw SymbolTable::UndefinedSymbolError { GetIdentifier() };
      }
      auto& symbol { result->get() };
      auto const& symbolType { symbol.GetType() };
      Type::VerifySameType( symbolType, GetExprNode()->GetType() );
      if( !symbolType->IsMut() )
      {
        throw Type::CannotAssignToImmutableError { GetIdentifier() };
      }

      auto const& val { GenerateNewValue( ctx, symbolType ) };
      symbol.SetVal( val );

      return {};
    }
#pragma endregion

  private:
    std::string m_identifier;
    ASTNodePtr m_exprNode;
  };
}