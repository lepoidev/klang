#pragma once

#include "KLangCommon.h"
#include "AST/Nodes/LiteralNode.h"
#include "AST/Types/IntegralType.h"

template <typename IntegralASTType, typename ValueTy>
class IntegralLiteralNode : public LiteralNode
{
#pragma region Type Enforcement
private:
  static_assert( std::is_integral_v<remove_cvref_t<ValueTy>>,
                 "Requires integral value type" );
  static_assert(
    std::is_base_of_v<IntegralType, remove_cvref_t<IntegralASTType>>,
    "Requires an ASTType derived from IntegralType" );
#pragma endregion

#pragma region Constructors / Destructors
public:
  IntegralLiteralNode( remove_cvref_t<ValueTy> const& val ) :
    LiteralNode(), m_val { val }
  {
    SetType( ASTType::CreateType<IntegralASTType>() );
  }
#pragma endregion

#pragma region Getters / Setters
public:
  ValueTy const GetValue() const
  {
    return m_val;
  };

protected:
  void SetValue( ValueTy const val )
  {
    m_val = val;
  }
#pragma endregion
protected:
  ValueTy m_val;
};