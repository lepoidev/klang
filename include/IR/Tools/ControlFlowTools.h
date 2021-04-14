#pragma once

#include "KLangCommon.h"

namespace IR
{
#pragma region Callback Types
  using ConditionalCallback = std::function<llvm::Value*()>;
  using BlockCreationCallback = std::function<void()>;
  using ConditionalChainPair =
    std::pair<ConditionalCallback, BlockCreationCallback>;
#pragma endregion
}