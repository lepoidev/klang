#pragma once

#include "KLangCommon.h"

namespace IR
{
  class IRGenerator
  {
#pragma region Constructors / Destructors
  public:
    IRGenerator() = delete;
    IRGenerator( std::string const& outputFile );
#pragma endregion

#pragma region IR Generation
  public:
    void GenerateIR( ASTNodePtr const& root );
#pragma endregion

  private:
    std::string m_outputFile;
    std::string m_moduleName;
  };
}