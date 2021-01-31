#include <vector>
#include <getopt.h>

#include "IsValidGrammar.h"

int main( int argc, char** argv )
{
  int curOpt {};
  int expectGrammarFailureFlag {};

  while( true )
  {
    struct option long_options[] {
      { "invalid-grammar", no_argument, &expectGrammarFailureFlag, 1 },
      { 0, 0, 0, 0 }
    };
    int optionIdx {};

    curOpt = getopt_long( argc, argv, "i", long_options, &optionIdx );

    if( curOpt == -1 )
    {
      break;
    }

    switch( curOpt )
    {
      case 0: break;
      case 'i': expectGrammarFailureFlag = 1; break;
      case '?': break;
      default: abort();
    }
  }

  auto const expectedResult { expectGrammarFailureFlag == 0 ? true : false };
  int numFails {};

  std::cout << "Expecting " << ( expectedResult ? "valid" : "invalid" )
            << " grammar" << std::endl;

  while( optind < argc )
  {
    std::filesystem::directory_entry dirEntry { argv[optind++] };
    std::cout << "\tValidating: " << dirEntry.path() << std::endl;
    auto const isValidGrammar { IsValidGrammar( dirEntry ) };
    if( isValidGrammar != expectedResult )
    {
      std::cout << "\t\t-> Failed" << std::endl;
      ++numFails;
    }
    else
    {
      std::cout << "\t\t-> Success" << std::endl;
    }
  }
  std::cout << "\tTotal Failures: " << numFails << std::endl;
  return numFails > 0;
}