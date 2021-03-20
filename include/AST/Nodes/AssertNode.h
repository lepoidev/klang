#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"
#include "BuiltInFunctions.h"

namespace AST
{
  class AssertNode : public Node
  {
#pragma region Constsructors / Destructors
  public:
    AssertNode( std::string const& expr,
                uint64_t const line,
                ASTNodePtr const& exprNode ) :
      Node {},
      m_expr { expr }, m_line { line }, m_exprNode { exprNode }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetExpr() const
    {
      return m_expr;
    }
    auto const GetLine() const
    {
      return m_line;
    }
    auto const& GetExprNode() const
    {
      return m_exprNode;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const fileName { ctx.GetModule().getSourceFileName() };
      auto const cond { GetExprNode()->GenerateIR( ctx ) };
      BuiltIn::Assert( ctx, fileName, GetExpr(), GetLine(), cond );
      return {};
    }
#pragma endregion

  private:
    std::string m_expr;
    uint64_t m_line;
    ASTNodePtr m_exprNode;
  };
}