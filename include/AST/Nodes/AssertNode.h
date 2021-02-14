#pragma once

#include "AST/Nodes/Node.h"
#include "BuiltInFunctions.h"

namespace AST
{
  class AssertNode : public Node
  {
#pragma region Constsructors / Destructors
  public:
    AssertNode( std::string const& file,
                std::string const& expr,
                uint64_t const line,
                ASTNodePtr const& exprNode ) :
      Node {},
      m_file { file }, m_expr { expr }, m_line { line }, m_exprNode { exprNode }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetFile() const
    {
      return m_file;
    }
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
      auto const cond { GetExprNode()->GenerateIR( ctx ) };
      BuiltIn::Assert( ctx, GetFile(), GetExpr(), GetLine(), cond );
      return {};
    }
#pragma endregion

  private:
    std::string m_file;
    std::string m_expr;
    uint64_t m_line;
    ASTNodePtr m_exprNode;
  };
}