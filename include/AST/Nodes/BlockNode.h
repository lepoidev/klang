#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class BlockNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    BlockNode() = delete;
    BlockNode( std::vector<ASTNodePtr> const& statements ) :
      Node {}, m_statements { statements }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetStatements() const
    {
      return m_statements;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      ctx.GetSymbolTable().PushNewScope();
      for( auto const& statement : GetStatements() )
      {
        statement->GenerateIR( ctx );
      }
      ctx.GetSymbolTable().PopScope();
      return {};
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
    std::vector<ASTNodePtr> GetChildren() const override
    {
      return GetStatements();
    }
#pragma endregion

  private:
    std::vector<ASTNodePtr> m_statements;
  };
}