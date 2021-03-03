#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/Node.h"

namespace AST
{
  class IdentifierNode : public Node
  {
#pragma region Constructors / Destructors
  public:
    IdentifierNode() = delete;
    IdentifierNode( std::string const& identifier ) :
      Node {}, m_identifier { identifier }
    {
    }
#pragma endregion

#pragma region Getters / Setters
  public:
    auto const GetIdentifier() const
    {
      return m_identifier;
    }
#pragma endregion

#pragma region IR Generation
  public:
    llvm::Value* GenerateIR( IR::Context const& ctx ) const final
    {
      return {};
    }
#pragma endregion

  private:
    std::string m_identifier;
  };
}