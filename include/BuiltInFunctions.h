#pragma once

#include "KLangCommon.h"
#include "Bootstrap.h"
#include "IR/Tools/CondBuilder.h"

namespace BuiltIn
{
  static void Assert( IR::Context const& ctx,
                      std::string const& file,
                      std::string const& expr,
                      uint64_t const line,
                      llvm::Value* const cond )
  {
    auto const condCB { [&]() {
      return ctx.GetIRBuilder().CreateICmpEQ( cond,
                                              ctx.GetIRBuilder().getFalse() );
    } };
    auto const blockCB { [&]() {
      auto const assertMessage { "Assertion failed in file \'" + file +
                                 "\' on line " + std::to_string( line ) +
                                 "\n\t\'" + expr + "\'\n" };
      auto const assertConstant { llvm::ConstantDataArray::getString(
        ctx.GetGlobalLLVMContext(), assertMessage ) };

      auto const assertGlobal { new llvm::GlobalVariable(
        ctx.GetModule(),
        assertConstant->getType(),
        true,
        llvm::GlobalValue::LinkageTypes::PrivateLinkage,
        assertConstant ) };
      Bootstrap::CallPrintf(
        ctx,
        ctx.GetIRBuilder().CreatePointerCast(
          assertGlobal, ctx.GetIRBuilder().getInt8Ty()->getPointerTo() ) );
      Bootstrap::CallExit( ctx, ctx.GetIRBuilder().getInt32( 1 ) );
    } };
    IR::CondBuilder condBuilder { ctx };
    condBuilder.AddConditional( condCB, blockCB );
    condBuilder.Build();
  }
}