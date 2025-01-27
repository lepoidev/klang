#pragma once

#include "KLangCommon.h"
#include "IR/Context.h"

namespace Bootstrap
{
  static void CallExit( IR::Context const& ctx, llvm::Value* exitVal )
  {
    auto constexpr funcName { "exit" };
    auto const retType { ctx.GetIRBuilder().getVoidTy() };
    std::vector<llvm::Type*> const paramTypes {
      ctx.GetIRBuilder().getInt32Ty()
    };
    auto const functionType { llvm::FunctionType::get(
      retType, paramTypes, false ) };
    auto const callable { ctx.GetModule().getOrInsertFunction( funcName,
                                                               functionType ) };

    if( exitVal->getType() != ctx.GetIRBuilder().getInt32Ty() )
    {
      exitVal = ctx.GetIRBuilder().CreateIntCast(
        exitVal, ctx.GetIRBuilder().getInt32Ty(), true );
    }
    ctx.GetIRBuilder().CreateCall( callable, exitVal );
  }

  static void CallPrintf( IR::Context const& ctx, llvm::Value* arg )
  {
    auto constexpr funcName { "printf" };
    auto const retType { ctx.GetIRBuilder().getInt32Ty() };
    std::vector<llvm::Type*> const paramTypes {
      ctx.GetIRBuilder().getInt8Ty()->getPointerTo()
    };
    auto const functionType { llvm::FunctionType::get(
      retType, paramTypes, true ) };
    auto const callable { ctx.GetModule().getOrInsertFunction( funcName,
                                                               functionType ) };
    ctx.GetIRBuilder().CreateCall( callable, arg );
  }
}
