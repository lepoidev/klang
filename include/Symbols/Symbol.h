#pragma once

#include "KLangCommon.h"

class Symbol
{
#pragma region Constructors / Destructors
public:
  Symbol() = delete;
  Symbol( std::string const& name, llvm::Value* val, ASTTypePtr const& type ) :
    m_name { name }, m_val { val }, m_type { type }
  {
  }
#pragma endregion

#pragma region Getters / Setters
public:
  auto const GetName() const
  {
    return m_name;
  }
  auto const GetVal() const
  {
    return m_val;
  }
  void SetVal( llvm::Value* val )
  {
    m_val = val;
  }
  auto const GetType() const
  {
    return m_type;
  }
#pragma endregion

private:
  std::string m_name;
  llvm::Value* m_val;
  ASTTypePtr m_type;
};