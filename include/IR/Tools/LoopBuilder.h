#pragma once

#include "KLangCommon.h"
#include "IR/Context.h"
#include "IR/Tools/CondBuilder.h"
#include "IR/Tools/ControlFlowTools.h"

namespace IR
{
  class LoopBuilder
  {
#pragma region Constructors / Destructors
  public:
    LoopBuilder( Context const& ctx ) : m_ctx { ctx }
    {
    }
#pragma endregion

#pragma region Loop Creation
  public:
    void SetConditional( ConditionalCallback const& condCB )
    {
      m_conditionalCallback = condCB;
    }
    void SetPreConditional( BlockCreationCallback const& blockCB )
    {
      m_preConditionalCallback = blockCB;
    }
    void SetPostConditional( BlockCreationCallback const& blockCB )
    {
      m_postConditionalCallback = blockCB;
    }
    void Build()
    {
      auto const insertBlock { m_ctx.GetIRBuilder().GetInsertBlock() };
      auto const curFunction { insertBlock->getParent() };
      auto const loopBeginBlock { llvm::BasicBlock::Create(
        m_ctx.GetGlobalLLVMContext(), "loop_begin" ) };
      auto const loopEndBlock { llvm::BasicBlock::Create(
        m_ctx.GetGlobalLLVMContext(), "loop_end" ) };

      m_ctx.GetIRBuilder().CreateBr( loopBeginBlock );

      curFunction->getBasicBlockList().push_back( loopBeginBlock );
      m_ctx.GetIRBuilder().SetInsertPoint( loopBeginBlock );

      if( m_preConditionalCallback )
      {
        m_preConditionalCallback();
      }

      CondBuilder condBuilder { m_ctx };
      condBuilder.AddConditional( m_conditionalCallback,
                                  m_postConditionalCallback );
      auto const exitLoopCallback { [&]() {
        m_ctx.GetIRBuilder().CreateBr( loopEndBlock );
      } };
      condBuilder.SetElse( exitLoopCallback );
      condBuilder.Build();

      if( !curFunction->getBasicBlockList().back().getTerminator() )
      {
        m_ctx.GetIRBuilder().CreateBr( loopEndBlock );
      }
      curFunction->getBasicBlockList().push_back( loopEndBlock );
      m_ctx.GetIRBuilder().SetInsertPoint( loopEndBlock );
    }
    void Reset()
    {
      m_conditionalCallback = nullptr;
      m_preConditionalCallback = nullptr;
      m_postConditionalCallback = nullptr;
    }
#pragma endregion

  private:
    ConditionalCallback m_conditionalCallback;
    BlockCreationCallback m_preConditionalCallback;
    BlockCreationCallback m_postConditionalCallback;
    Context const& m_ctx;
  };
}