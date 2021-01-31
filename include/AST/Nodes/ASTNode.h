#pragma once

#include "KLangCommon.h"

class ASTNode
{
public:
#pragma region Constructors / Destructors
  ASTNode() : m_type {}
  {
  }
  virtual ~ASTNode() = default;
  virtual llvm::Value* GenerateIR( IRContext& ctx ) const = 0;
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

#pragma region Static Functions
public:
  template <typename NodeTy>
  static auto Cast( ASTNodePtr const& nodePtr )
  {
    return std::dynamic_pointer_cast<NodeTy>( nodePtr );
  }

  template <typename ASTNodeTy, typename... Args>
  static auto CreateNode( Args&&... args )
  {
    return std::make_shared<ASTNodeTy>( std::forward<Args>( args )... );
  }
#pragma endregion

private:
  ASTTypePtr m_type;
};