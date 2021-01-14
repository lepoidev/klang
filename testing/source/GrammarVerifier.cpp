#include <vector>
#include <getopt.h>

#include "IsValidGrammar.h"

bool VerifyFiles( std::vector<std::filesystem::directory_entry> const& files,
                  bool const expectGrammarFailure )
{
  auto const verifyGrammar { [&](
                               std::filesystem::directory_entry const& file ) {
    auto const isValidGrammar { IsValidGrammar( file ) };
    if( expectGrammarFailure )
    {
      return !isValidGrammar;
    }
    return isValidGrammar;
  } };
  return std::all_of( files.begin(), files.end(), verifyGrammar );
}

int main( int argc, char** argv )
{
  int curOpt {};
  int expectGrammarFailureFlag {};

  while( true )
  {
    static struct option long_options[] = {
      { "invalid-grammar", no_argument, &expectGrammarFailureFlag, 1 },
      { 0, 0, 0, 0 }
    };
    int optionIdx {};

    curOpt = getopt_long( argc, argv, "vsi", long_options, &optionIdx );

    if( curOpt == -1 )
    {
      break;
    }

    switch( curOpt )
    {
      case 0: break;
      case 'i': break;
      case '?': break;
      default: abort();
    }
  }

  std::vector<std::filesystem::directory_entry> files {};

  while( optind < argc )
  {
    files.emplace_back( argv[optind++] );
  }

  if( VerifyFiles( files, expectGrammarFailureFlag != 0 ) )
  {
    return 0;
  }

  return 1;
}