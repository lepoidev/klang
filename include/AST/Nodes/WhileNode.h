#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"
#include "IR/Tools/LoopBuilder.h"

namespace AST
{
  class WhileNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    WhileNode() = delete;
    WhileNode( ASTNodePtr const& loopCond, ASTNodePtr const& loopBody ) :
      m_loopCond { loopCond }, m_loopBody { loopBody }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const& GetLoopCond() const
    {
      return m_loopCond;
    }
    auto const& GetLoopBody() const
    {
      return m_loopBody;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const condCallback { [&]() {
        return GetLoopCond()->GenerateIR( ctx );
      } };
      auto const loopBodyCallback { [&]() {
        GetLoopBody()->GenerateIR( ctx );
      } };

      IR::LoopBuilder loopBuilder { ctx };
      loopBuilder.SetConditional( condCallback );
      loopBuilder.SetPostConditional( loopBodyCallback );
      loopBuilder.Build();
      return {};
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    ACCEPT_VISITOR;
    std::vector<ASTNodePtr> GetChildren() const override
    {
      return { GetLoopCond(), GetLoopBody() };
    }
#pragma endregion

  private:
    ASTNodePtr m_loopCond;
    ASTNodePtr m_loopBody;
  };
}