#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/UnaryNode.h"

namespace AST
{
  class ReturnNode : public UnaryNode
  {
    using UnaryNode::UnaryNode;
#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      auto const& node { GetNode() };
      if( node == nullptr )
      {
        ctx.GetIRBuilder().CreateRetVoid();
      }
      else
      {
        auto const retVal { node->GenerateIR( ctx ) };
        ctx.GetIRBuilder().CreateRet( retVal );
      }
      return {};
    }
#pragma endregion
  };
}