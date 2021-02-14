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
      Bootstrap::CallExit( ctx, ctx.GetIRBuilder().getInt32( 1 ) );
    } };
    IR::CondBuilder condBuilder { ctx };
    condBuilder.AddConditional( condCB, blockCB );
    condBuilder.Build();
  }
}