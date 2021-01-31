#pragma once

#include "Tools.h"

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_os_ostream.h>

#include "AST/ASTCommon.h"