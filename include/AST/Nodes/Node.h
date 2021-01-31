#pragma once

#include "KLangCommon.h"

namespace AST
{
  class Node
  {
#pragma region Constructors / Destructors
  public:
    Node() : m_type {}
    {
    }
    virtual ~Node() = default;
#pragma endregion

#pragma region IR Generation
  public:
    virtual llvm::Value* GenerateIR( IR::Context& ctx ) const = 0;
#pragma endregion

#pragma region Getters / Setter
  protected:
    void SetType( ASTTypePtr const& otherTy )
    {
      m_type = otherTy;
    }

  public:
    ASTTypePtr const GetType() const
    {
      return m_type;
    }
#pragma endregion

  private:
    ASTTypePtr m_type;
  };

#pragma region Namespace Functions
  template <typename NodeTy>
  auto CastNode( ASTNodePtr const& nodePtr )
  {
    return std::dynamic_pointer_cast<NodeTy>( nodePtr );
  }

  template <typename ASTNodeTy, typename... Args>
  auto CreateNode( Args&&... args )
  {
    return std::make_shared<ASTNodeTy>( std::forward<Args>( args )... );
  }
#pragma endregion
}