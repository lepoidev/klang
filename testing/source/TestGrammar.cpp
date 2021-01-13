#include "TestGrammar.h"

#include <KLexer.h>
#include <KParser.h>

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>

#include <tree/ParseTree.h>
#include <tree/ParseTreeWalker.h>

using recursive_directory_iterator =
  std::filesystem::recursive_directory_iterator;

bool IsValidFile( std::filesystem::directory_entry const& dirEntry )
{
  try
  {
    std::string pathToFile { dirEntry.path() };
    antlr4::ANTLRFileStream afs { pathToFile };
    KLexer lexer { &afs };
    antlr4::CommonTokenStream tokens { &lexer };
    KParser parser { &tokens };

    // memory managed by antlr
    parser.file();
    return true;
  }
  catch( ... )
  {
    return false;
  }
}

int main( int argc, char** argv )
{
  if( argc != 2 )
  {
    std::cerr << "Please provide path to tests" << std::endl;
    return -1;
  }

  int numFails { 0 };

  std::string const pathToSourceFile { argv[1] };
  for( auto const& dirEntry : recursive_directory_iterator( pathToSourceFile ) )
  {
    if( dirEntry.is_regular_file() )
    {
      auto const& path { dirEntry.path() };
      auto const ext { path.extension() };
      auto const iskFile { ext == ".k" };

      if( !iskFile )
      {
        continue;
      }

      std::cout << "Verifying grammar for: " << dirEntry.path() << std::endl;
      if( !IsValidFile( dirEntry ) )
      {
        std::cout << "\tFailed!" << std::endl;
        ++numFails;
      }
    }
  }

  return numFails;
}
