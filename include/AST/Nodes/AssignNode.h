#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/UnaryNode.h"
#include "AST/Types/Type.h"

namespace AST
{
  class AssignNode : public UnaryNode
  {
#pragma region Constructors / Destructors
  public:
    AssignNode( std::string const& identifier, ASTNodePtr const& exprNode ) :
      UnaryNode { exprNode }, m_identifier { identifier }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetIdentifier() const
    {
      return m_identifier;
    }
    auto const HasExpr() const
    {
      return GetNode() != nullptr;
    }
#pragma endregion

#pragma region IR Generation
  protected:
    auto const GenerateNewValue( IR::Context const& ctx,
                                 ASTTypePtr const& targetType ) const
    {
      if( HasExpr() )
      {
        return GetNode()->GenerateIR( ctx );
      }
      return targetType->GenerateDefaultIRInst( ctx );
    }

  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const result { ctx.GetSymbolTable().ResolveSymbol( GetIdentifier(),
                                                              true ) };
      auto& symbol { result->get() };
      auto const& symbolType { symbol.GetType() };
      Type::VerifySameType( symbolType, GetNode()->GetType() );
      if( !symbolType->IsMut() )
      {
        throw Type::CannotAssignToImmutableError { GetIdentifier() };
      }

      auto const& val { GenerateNewValue( ctx, symbolType ) };
      ctx.GetIRBuilder().CreateStore( val, symbol.GetPtr() );

      return {};
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion

  private:
    std::string m_identifier;
  };
}