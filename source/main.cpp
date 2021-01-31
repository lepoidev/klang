#include <iostream>

#include <KLexer.h>
#include <KParser.h>

#include <ANTLRFileStream.h>
#include <CommonTokenStream.h>

#include <tree/ParseTree.h>
#include <tree/ParseTreeWalker.h>

#include "AST/Nodes/Node.h"
#include "AST/ASTGenerator.h"
#include "IR/IRGenerator.h"

int main( int argc, char** argv )
{
  if( argc < 3 )
  {
    std::cout << "Expecting: " << argv[0] << " <path_to_input> <path_to_output>"
              << std::endl;
    return 1;
  }

  std::string inputFile { argv[1] };
  std::string outputFile { argv[2] };

  antlr4::ANTLRFileStream afs { inputFile };
  KLexer lexer { &afs };
  antlr4::CommonTokenStream tokens { &lexer };
  KParser parser { &tokens };

  // memory managed by antlr
  auto const parseTree { parser.file() };

  // Create AST
  AST::ASTGenerator astGenerator {};
  auto const astRoot { static_cast<ASTNodePtr>(
    astGenerator.visit( parseTree ) ) };

  // Generate IR
  IR::IRGenerator irGenerator { outputFile };
  irGenerator.GenerateIR( astRoot );

  return 0;
}
