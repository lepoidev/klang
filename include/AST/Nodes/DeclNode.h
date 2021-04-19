#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/UnaryNode.h"

namespace AST
{
  class DeclNode : public UnaryNode
  {
#pragma region Constructors / Destructors
  public:
    DeclNode() = delete;
    DeclNode( std::string const& identifier,
              ASTTypePtr const& declType,
              ASTNodePtr const& initializerNode ) :
      UnaryNode { initializerNode },
      m_identifier { identifier }, m_declType { declType }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetIdentifier() const
    {
      return m_identifier;
    }
    auto const& GetDeclType() const
    {
      return m_declType;
    }

  protected:
    auto const HasInitializer() const
    {
      return GetNode() != nullptr;
    }
#pragma endregion

#pragma region IR Generation
  protected:
    auto const GenerateInitializer( IR::Context const& ctx ) const
    {
      if( HasInitializer() )
      {
        return GetNode()->GenerateIR( ctx );
      }
      return GetDeclType()->GenerateDefaultIRInst( ctx );
    }

  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      if( HasInitializer() )
      {
        Type::VerifySameType( GetDeclType(), GetNode()->GetType() );
      }

      auto const& initializer { GenerateInitializer( ctx ) };
      auto const& ptr { GetNode()->GetType()->GenerateStackAllocation(
        ctx, GetIdentifier() ) };
      ctx.GetIRBuilder().CreateStore( initializer, ptr );
      ctx.GetSymbolTable().AddSymbol( GetIdentifier(), GetDeclType(), ptr );
      return {};
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion

  private:
    std::string m_identifier;
    ASTTypePtr m_declType;
  };
}