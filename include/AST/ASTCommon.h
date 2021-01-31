#pragma once
#include <memory>
#include "IR/IRContext.h"

class ASTNode;
class ASTType;

using ASTNodePtr = std::shared_ptr<ASTNode>;
using ASTTypePtr = std::shared_ptr<ASTType>;
 