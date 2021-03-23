#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/UnaryNode.h"
#include "BuiltInFunctions.h"

namespace AST
{
  class AssertNode : public UnaryNode
  {
#pragma region Constructors / Destructors
  public:
    AssertNode( std::string const& expr,
                uint64_t const line,
                ASTNodePtr const& exprNode ) :
      UnaryNode { exprNode },
      m_expr { expr }, m_line { line }
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
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const fileName { ctx.GetModule().getSourceFileName() };
      auto const cond { GetNode()->GenerateIR( ctx ) };
      BuiltIn::Assert( ctx, fileName, GetExpr(), GetLine(), cond );
      return {};
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
#pragma endregion

  private:
    std::string m_expr;
    uint64_t m_line;
  };
}