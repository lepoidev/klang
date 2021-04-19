#pragma once

#include "KLangCommon.h"

class Symbol
{
#pragma region Constructors / Destructors
public:
  Symbol() = delete;
  Symbol( std::string const& name, ASTTypePtr const& type ) :
    m_name { name }, m_type { type }
  {
  }
#pragma endregion

#pragma region Getters / Setters
public:
  auto const GetName() const
  {
    return m_name;
  }
  auto const GetType() const
  {
    return m_type;
  }
#pragma endregion

private:
  std::string m_name;
  ASTTypePtr m_type;
};