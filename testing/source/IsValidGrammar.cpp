#include "IsValidGrammar.h"

#include <KLexer.h>
#include <KParser.h>

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>

#include <tree/ParseTree.h>
#include <tree/ParseTreeWalker.h>

bool IsValidGrammar( std::filesystem::directory_entry const& dirEntry )
{
  std::string pathToFile { dirEntry.path() };

  antlr4::ANTLRFileStream afs { pathToFile };
  KLexer lexer { &afs };
  antlr4::CommonTokenStream tokens { &lexer };
  KParser parser { &tokens };

  // memory managed by antlr
  parser.file();
  auto const numErrs { parser.getNumberOfSyntaxErrors() };
  return numErrs == 0;
}
