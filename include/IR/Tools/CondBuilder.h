#pragma once

#include "KLangCommon.h"
#include "IR/Context.h"

namespace IR
{
  class CondBuilder
  {
#pragma region Callback Types
  public:
    using ConditionalCallback = std::function<llvm::Value*()>;
    using BlockCreationCallback = std::function<void()>;
    using ConditionalChainPair =
      std::pair<ConditionalCallback, BlockCreationCallback>;
#pragma endregion

#pragma region Constructors / Destructors
  public:
    CondBuilder( Context const& ctx ) : m_ctx { ctx }
    {
    }
#pragma endregion

#pragma region Conditional Creation
  public:
    void AddConditional( ConditionalCallback const& condCB,
                         BlockCreationCallback const& blockCB )
    {
      m_conditionalChainPairs.push_back( { condCB, blockCB } );
    }
    void SetElse( BlockCreationCallback const& blockCB )
    {
      m_elseBlockCallback = blockCB;
    }
    void Build()
    {
      auto const insertBlock { m_ctx.GetIRBuilder().GetInsertBlock() };
      auto const curFunction { insertBlock->getParent() };
      auto const mergeBlock { llvm::BasicBlock::Create(
        m_ctx.GetGlobalLLVMContext(), "merge" ) };

      for( auto const& [condCB, blockCB] : m_conditionalChainPairs )
      {
        auto const thenBlock { llvm::BasicBlock::Create(
          m_ctx.GetGlobalLLVMContext(), "then" ) };
        auto const nextBlock { llvm::BasicBlock::Create(
          m_ctx.GetGlobalLLVMContext(), "next" ) };

        auto const cond { condCB() };
        m_ctx.GetIRBuilder().CreateCondBr( cond, thenBlock, nextBlock );
        curFunction->getBasicBlockList().push_back( thenBlock );
        m_ctx.GetIRBuilder().SetInsertPoint( thenBlock );

        blockCB();

        if( not( curFunction->getBasicBlockList().back().getTerminator() ) )
          m_ctx.GetIRBuilder().CreateBr( mergeBlock );
        curFunction->getBasicBlockList().push_back( nextBlock );
        m_ctx.GetIRBuilder().SetInsertPoint( nextBlock );
      }

      if( m_elseBlockCallback )
      {
        m_elseBlockCallback();
      }

      if( not( curFunction->getBasicBlockList().back().getTerminator() ) )
        m_ctx.GetIRBuilder().CreateBr( mergeBlock );
      curFunction->getBasicBlockList().push_back( mergeBlock );
      m_ctx.GetIRBuilder().SetInsertPoint( mergeBlock );

      Reset();
    }
    void Reset()
    {
      m_conditionalChainPairs.clear();
      m_elseBlockCallback = nullptr;
    }
#pragma endregion

  private:
    std::vector<ConditionalChainPair> m_conditionalChainPairs;
    BlockCreationCallback m_elseBlockCallback;
    Context const& m_ctx;
  };
}
