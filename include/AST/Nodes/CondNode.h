#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"
#include "IR/Tools/CondBuilder.h"

namespace AST
{
  class CondNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    CondNode( ASTNodePtr const& condExpr,
              ASTNodePtr const& thenStatement,
              ASTNodePtr const elseStatement = nullptr ) :
      m_condExpr { condExpr },
      m_thenStatement { thenStatement }, m_elseStatement { elseStatement }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetCondExpr() const
    {
      return m_condExpr;
    }
    auto const& GetThenStatement() const
    {
      return m_thenStatement;
    }
    auto const& GetElseStatement() const
    {
      return m_elseStatement;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const exprCallback { [&]() {
        return GetCondExpr()->GenerateIR( ctx );
      } };
      auto const thenCallback { [&]() {
        GetThenStatement()->GenerateIR( ctx );
      } };
      IR::CondBuilder::BlockCreationCallback elseCallback {};
      if( GetElseStatement() )
        elseCallback = [&]() { GetElseStatement()->GenerateIR( ctx ); };

      IR::CondBuilder condBuilder { ctx };
      condBuilder.AddConditional( exprCallback, thenCallback );
      condBuilder.SetElse( elseCallback );
      condBuilder.Build();

      return {};
    }

#pragma endregion

  private:
    ASTNodePtr m_condExpr;
    ASTNodePtr m_thenStatement;
    ASTNodePtr m_elseStatement;
  };
}