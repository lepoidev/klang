#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class DeclNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    DeclNode() = delete;
    DeclNode( std::string const& identifier,
              ASTTypePtr const& declType,
              ASTNodePtr const& initializerNode ) :
      m_identifier { identifier },
      m_declType { declType }, m_initializerNode { initializerNode }
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
    auto const& GetInitializerNode() const
    {
      return m_initializerNode;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const val { GetInitializerNode()->GenerateIR( ctx ) };
      ctx.GetSymbolTable().AddSymbol( GetIdentifier(), val, GetDeclType() );
      return {};
    }
#pragma endregion

  private:
    std::string m_identifier;
    ASTTypePtr m_declType;
    ASTNodePtr m_initializerNode;
  };
}