#pragma once

#include "KLangCommon.h"
#include "IR/Context.h"
#include "AST/Visitor/Visitor.h"

#define ACCEPT_VISITOR                                                         \
public:                                                                        \
  std::any Accept( Visitor& visitor ) override                                 \
  {                                                                            \
    return visitor.Visit( *this );                                             \
  }

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
    virtual llvm::Value* GenerateIR( IR::Context const& ctx ) const = 0;
#pragma endregion

#pragma region Getters / Setter
  public:
    void SetType( ASTTypePtr const& otherTy )
    {
      m_type = otherTy;
    }
    auto const GetType() const
    {
      return m_type;
    }
#pragma endregion

#pragma region Visitor Acceptance
  public:
    virtual std::any Accept( Visitor& visitor )
    {
      return visitor.Visit( *this );
    }
    virtual std::vector<ASTNodePtr> GetChildren() const
    {
      return {};
    }
#pragma endregion

  private:
    ASTTypePtr m_type;
  };

#pragma region Namespace Functions
  template <typename NodeTy>
  static auto CastNode( ASTNodePtr const& nodePtr )
  {
    return std::dynamic_pointer_cast<NodeTy>( nodePtr );
  }

  template <typename ASTNodeTy, typename... Args>
  static auto CreateNode( Args&&... args )
  {
    std::make_shared<ASTNodeTy>( std::forward<Args>( args )... );
  }

  template <typename ASTNodeTy, typename... Args>
  static auto CreateGenericNode( Args&&... args )
  {
    return CastNode<Node>(
      std::make_shared<ASTNodeTy>( std::forward<Args>( args )... ) );
  }

  template <typename ASTNodeTy>
  using NodePtr = std::shared_ptr<ASTNodeTy>;
#pragma endregion
}