#include "AST/ASTGenerator.h"

#include "AST/ASTNodes.h"
#include "AST/ASTTypes.h"

namespace AST
{
  antlrcpp::Any ASTGenerator::visitFile( KParser::FileContext* ctx )
  {
    std::vector<ASTNodePtr> statements {};
    for( auto& functionDeclare : ctx->functionDeclare() )
    {
      statements.push_back(
        static_cast<ASTNodePtr>( visit( functionDeclare ) ) );
    }
    return CreateGenericNode<FileNode>( statements );
  }

  antlrcpp::Any
  ASTGenerator::visitFunctionDeclare( KParser::FunctionDeclareContext* ctx )
  {
    auto const& functionIdentifier { ctx->functionIdentifier() };
    std::string const functionName {
      functionIdentifier->functionName->getText()
    };

    auto const hasReturnType { functionIdentifier->type() != nullptr };
    ASTTypePtr const& returnType { hasReturnType ?
                                     static_cast<ASTTypePtr>(
                                       visit( functionIdentifier->type() ) ) :
                                     nullptr };

    std::vector<ASTTypePtr> paramTypes {};
    auto const& funcBody { static_cast<ASTNodePtr>(
      visit( ctx->statement() ) ) };
    return CreateGenericNode<FunctionNode>(
      functionName, returnType, paramTypes, funcBody );
  }

#pragma region Literals
  antlrcpp::Any
  ASTGenerator::visitIntegerLiteral( KParser::IntegerLiteralContext* ctx )
  {
    std::string const text { ctx->getText() };
    auto const val { std::stoi( text ) };
    return CreateGenericNode<IntegerLiteralNode>( val );
  }

  antlrcpp::Any
  ASTGenerator::visitBooleanLiteral( KParser::BooleanLiteralContext* ctx )
  {
    std::string const text { ctx->getText() };
    auto const val { text == "true" };
    return CreateGenericNode<BooleanLiteralNode>( val );
  }
#pragma endregion

#pragma region Statements
  antlrcpp::Any ASTGenerator::visitFunctionCallStatement(
    KParser::FunctionCallStatementContext* ctx )
  {
    return visit( ctx->functionCall() );
  }

  antlrcpp::Any
  ASTGenerator::visitReturnStatement( KParser::ReturnStatementContext* ctx )
  {
    auto const hasExpr { ctx->expr() != nullptr };
    ASTNodePtr const expr { hasExpr ?
                              static_cast<ASTNodePtr>( visit( ctx->expr() ) ) :
                              nullptr };
    return CreateGenericNode<ReturnNode>( expr );
  }

  antlrcpp::Any
  ASTGenerator::visitBlockStatement( KParser::BlockStatementContext* ctx )
  {
    std::vector<ASTNodePtr> statements {};
    for( auto& statement : ctx->statement() )
    {
      statements.push_back( static_cast<ASTNodePtr>( visit( statement ) ) );
    }
    return CreateGenericNode<BlockNode>( statements );
  }

  antlrcpp::Any ASTGenerator::visitConditionalStatement(
    KParser::ConditionalStatementContext* ctx )
  {
    auto const condExpr { static_cast<ASTNodePtr>(
      visit( ctx->condition()->expr() ) ) };
    auto const thenStatement { static_cast<ASTNodePtr>(
      visit( ctx->statement().at( 0 ) ) ) };
    ASTNodePtr const elseStatement { ctx->statement().size() > 1 ?
                                       static_cast<ASTNodePtr>(
                                         visit( ctx->statement().at( 1 ) ) ) :
                                       nullptr };
    return CreateGenericNode<CondNode>(
      condExpr, thenStatement, elseStatement );
  }

  antlrcpp::Any ASTGenerator::visitWhileLoop( KParser::WhileLoopContext* ctx )
  {
    auto const condExpr { static_cast<ASTNodePtr>(
      visit( ctx->condition() ) ) };
    auto loopBody { static_cast<ASTNodePtr>( visit( ctx->statement() ) ) };

    if( std::dynamic_pointer_cast<BlockNode>( loopBody ) == nullptr )
    {
      loopBody =
        CreateGenericNode<BlockNode>( std::vector<ASTNodePtr> { loopBody } );
    }

    return CreateGenericNode<WhileNode>( condExpr, loopBody );
  }
#pragma endregion

  antlrcpp::Any
  ASTGenerator::visitBooleanExpr( KParser::BooleanExprContext* ctx )
  {
    auto const [left, right] { VisitLR( ctx ) };
    if( auto const& eqOp { ctx->equalityOperation() }; eqOp != nullptr )
    {
      if( eqOp->IsEqual() != nullptr )
      {
        return CreateGenericNode<EQNode>( left, right );
      }
      else if( eqOp->NotIsEqual() != nullptr )
      {
        return CreateGenericNode<NEQNode>( left, right );
      }
    }
    else if( auto const& cmpOp { ctx->comparisonOperation() };
             cmpOp != nullptr )
    {
      if( cmpOp->CloseAngle() != nullptr )
      {
        return CreateGenericNode<LTNode>( left, right );
      }
      else if( cmpOp->LessEqual() != nullptr )
      {
        return CreateGenericNode<LTENode>( left, right );
      }
      else if( cmpOp->OpenAngle() != nullptr )
      {
        return CreateGenericNode<GTNode>( left, right );
      }
      else if( cmpOp->GreaterEqual() != nullptr )
      {
        return CreateGenericNode<GTENode>( left, right );
      }
    }
    return visitChildren( ctx );
  }

  antlrcpp::Any
  ASTGenerator::visitNonBooleanExpr( KParser::NonBooleanExprContext* ctx )
  {
    auto const& [left, right] { VisitLR( ctx ) };
    if( auto const& addOp { ctx->additiveOperation() }; addOp != nullptr )
    {
      if( addOp->Plus() != nullptr )
      {
        return CreateGenericNode<AddNode>( left, right );
      }
      else if( addOp->Minus() != nullptr )
      {
        return CreateGenericNode<SubNode>( left, right );
      }
    }
    else if( auto const& mulOp { ctx->multiplicativeOperation() } )
    {
      if( mulOp->Star() != nullptr )
      {
        return CreateGenericNode<MulNode>( left, right );
      }
      else if( mulOp->Div() != nullptr )
      {
        return CreateGenericNode<DivNode>( left, right );
      }
    }
    return visitChildren( ctx );
  }

  antlrcpp::Any ASTGenerator::visitBasicExpr( KParser::BasicExprContext* ctx )
  {
    return visitChildren( ctx );
  }

  antlrcpp::Any ASTGenerator::visitUnaryExpr( KParser::UnaryExprContext* ctx )
  {
    auto const& expr { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
    auto const& unaryOp { ctx->unaryOperation() };
    if( unaryOp->Minus() != nullptr )
    {
      return CreateGenericNode<SubNode>(
        CreateGenericNode<IntegerLiteralNode>( 0 ), expr );
    }
    else if( unaryOp->Plus() != nullptr )
    {
      return CreateGenericNode<AddNode>(
        CreateGenericNode<IntegerLiteralNode>( 0 ), expr );
    }
    return visitChildren( ctx );
  }

#pragma region Built In
  antlrcpp::Any ASTGenerator::visitAssertExpr( KParser::AssertExprContext* ctx )
  {
    auto const exprNode { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
    auto const expr { ctx->expr()->getText() };
    auto const line { ctx->getStart()->getLine() };
    return CreateGenericNode<AssertNode>( expr, line, exprNode );
  }
#pragma endregion

  antlrcpp::Any
  ASTGenerator::visitIdentifierExpr( KParser::IdentifierExprContext* ctx )
  {
    std::string const identifier { ctx->Identifier()->getText() };
    return CreateGenericNode<IdentifierNode>( identifier );
  }

  antlrcpp::Any ASTGenerator::visitCondition( KParser::ConditionContext* ctx )
  {
    return visit( ctx->expr() );
  }
#pragma region Declaration
  antlrcpp::Any ASTGenerator::visitAutoDecl( KParser::AutoDeclContext* ctx )
  {
    std::string const identifier { ctx->Identifier()->getText() };
    auto const isMutable { ctx->Mut() != nullptr };
    auto const& exprNode { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
    auto declType { exprNode->GetType()->Clone() };
    declType->SetMut( isMutable );
    return CreateGenericNode<DeclNode>( identifier, declType, exprNode );
  }

  antlrcpp::Any
  ASTGenerator::visitEmptyInitDecl( KParser::EmptyInitDeclContext* ctx )
  {
    std::string const identifier { ctx->Identifier()->getText() };
    auto const declType { static_cast<ASTTypePtr>( visit( ctx->type() ) ) };
    return CreateGenericNode<DeclNode>( identifier, declType, ASTNodePtr {} );

    return {};
  }

  antlrcpp::Any ASTGenerator::visitInitDecl( KParser::InitDeclContext* ctx )
  {
    std::string const identifier { ctx->Identifier()->getText() };
    auto const declType { static_cast<ASTTypePtr>( visit( ctx->type() ) ) };
    auto const& exprNode { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
    return CreateGenericNode<DeclNode>( identifier, declType, exprNode );

    return {};
  }
#pragma endregion

#pragma region Assignment
  antlrcpp::Any
  ASTGenerator::visitBasicAssign( KParser::BasicAssignContext* ctx )
  {
    std::string const identifier { ctx->Identifier()->getText() };
    auto const& exprNode { static_cast<ASTNodePtr>( visit( ctx->expr() ) ) };
    return CreateGenericNode<AssignNode>( identifier, exprNode );
  }
#pragma endregion

#pragma region Types
  antlrcpp::Any
  ASTGenerator::visitPrimitiveType( KParser::PrimitiveTypeContext* ctx )
  {
    if( ctx->Integer() )
    {
      return CreateGenericType<IntegerType>();
    }
    else if( ctx->Bool() )
    {
      return CreateGenericType<BooleanType>();
    }
    return {};
  }

  antlrcpp::Any ASTGenerator::visitType( KParser::TypeContext* ctx )
  {
    auto astType { static_cast<ASTTypePtr>( visit( ctx->rawType() ) ) };
    auto const isMutable { ctx->Mut() != nullptr };
    astType->SetMut( isMutable );
    return astType;
  }
#pragma endregion
}