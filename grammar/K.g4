grammar K
    ;

file
    : functionDeclare* EOF
    ;

// statements

statement
    : conditionalStatement
    | loopStatement
    | declarationStatement
    | assignmentStatement
    | functionCallStatement
    | returnStatement
    | breakStatement
    | continueStatement
    | blockStatement
    ;

loopStatement
    : While condition statement                  # condLoop
    | For (Mut)? Identifier In expr statement    # iteratorLoop
    | Repeat statement Until condition Semicolon # untilLoop
    ;

conditionalStatement
    : If condition statement (Else statement)?
    ;

condition
    : OpenPar expr ClosePar
    ;

assignmentStatement
    : Identifier Assign Null Semicolon # emptyAssign
    | Identifier Assign expr Semicolon # basicAssign
    ;

blockStatement
    : OpenBrace statement* CloseBrace
    ;

breakStatement
    : Break Semicolon
    ;

continueStatement
    : Continue Semicolon
    ;

declarationStatement
    : type Mut Identifier (Assign Null)? Semicolon    # emptyMutInitDecl
    | type Identifier (Assign Null)? Semicolon        # emptyConstInitDecl
    | type Mut Identifier Assign expr Semicolon       # initMutDecl
    | type Identifier Assign expr Semicolon           # initConstDecl
    | (Let)? Mut Identifier Assign expr Semicolon     # autoMutDecl
    | Let Identifier Assign expr Semicolon            # autoConstDecl
    ;

globalDeclaration
    : type Mut Identifier Assign expr Semicolon   # initMutGlobalDecl
    | type Identifier Assign expr Semicolon       # initConstGlobalDecl
    | (Let)? Mut Identifier Assign expr Semicolon # autoMutGlobalDecl
    | Let Identifier Assign expr Semicolon        # autoConstGlobalDecl
    ;

returnStatement
    : Return Semicolon | Return expr Semicolon
    ;

// literals

literal
    : BooleanLiteral # BooleanLiteral
    | BinaryLiteral  # BinaryLiteral
    | HexLiteral     # HexLiteral
    | IntegerLiteral # IntegerLiteral
    | CharLiteral    # CharLiteral
    | StringLiteral  # StringLiteral
    | FloatLiteral   # FloatLiteral
    ;

vectorLiteral
    : OpenSqr (expr (Comma expr)*)? CloseSqr
    ;

tupleLiteral
    : OpenPar (expr Comma (expr (Comma expr)*)?)
    ;

// exprs

expr
    : OpenPar expr ClosePar                                 # basicExpr
    | As OpenAngle type CloseAngle OpenPar expr ClosePar    # castExpr
    | literal                                               # basicExpr
    | vectorLiteral                                         # basicExpr
    | tupleLiteral                                          # basicExpr
    | Identifier                                            # identifierExpr
    | functionCall                                          # basicExpr
    | left=expr DotDot right=expr                           # rangeExpr
    | <assoc=right> unaryOperation expr                     # unaryExpr
    | <assoc=right> left=expr powOperation right=expr       # nonBooleanExpr
    | left=expr multiplicativeOperaton right=expr           # nonBooleanExpr
    | left=expr additiveOperation right=expr                # nonBooleanExpr
    | left=expr shiftOperation right=expr                   # shiftExpr
    | left=expr bitwiseOperation right=expr                 # bitwiseExpr
    | left=expr linAlgOperation right=expr                  # nonBooleanExpr
    | left=expr comparisonOperation right=expr              # booleanExpr
    | left=expr equalityOperation right=expr                # booleanExpr
    | left=expr conjunctiveOperation right=expr             # booleanExpr
    | left=expr disjunctionOperation right=expr             # booleanExpr
    | <assoc=right> left=expr In right=expr                 # inExpr
    ;

// functions

functionIdentifier
    : Function functionName=(Identifier | Main) parameters (Returns type)?
    ;

functionDeclare
    : functionIdentifier statement
    ;

parameters
    : OpenPar (type Colon Identifier (Comma type Colon Identifier)*)? ClosePar
    ;

arguments
    : OpenPar (expr (Comma expr)*)? ClosePar
    ;

functionCall
    : builtInFunctionCall   # builtinFunctionCall
    | Identifier arguments  # userFunctionCall
    ;

builtInFunctionCall
    : Print OpenPar expr ClosePar       # printExpr
    | Size OpenPar expr ClosePar        # sizeExpr
    | Rows OpenPar expr ClosePar        # rowsExpr
    | Cols OpenPar expr ClosePar        # colsExpr
    | Copy OpenPar expr ClosePar        # copyExpr
    | DeepCopy OpenPar expr ClosePar    # deepcopyExpr
    | Assert OpenPar expr ClosePar      # assertExpr
    | Reverse OpenPar expr CloseAngle   # reverseExpr
    ;

functionCallStatement
    : functionCall Semicolon
    ;

// type

rawType
    : modifiedType
    | vectorType
    | matrixType
    ;

type
    : rawType (Mut)?
    ;

typedecl
    : type
    | Let
    ;

modifiedType
    : baseType
    | customType
    ;

baseType
    : Integer
    | Char
    | Bool
    | Float
    //| IntType
    | String
    ;

customType
    : Identifier
    ;

vectorType
    : Vector OpenAngle type CloseAngle
    ;

matrixType
    : Matrix OpenAngle type CloseAngle
    ;

equalityOperation
    : IsEqual
    | NotIsEqual
    ;

// operations
powOperation
    : Hat
    ;

unaryOperation
    : Plus
    | Minus
    | BwNot
    | Not
    ;

comparisonOperation
    : CloseAngle //Less
    | LessEqual
    | OpenAngle //Greater
    | GreaterEqual
    ;

conjunctiveOperation
    : And
    ;

disjunctionOperation
    : Or
    ;

booleanOperation
    : conjunctiveOperation
    | disjunctionOperation
    ;

additiveOperation
    : Plus
    | Minus
    ;

multiplicativeOperaton
    : Star
    | Div
    | Rem
    | Modulo
    ;

linAlgOperation
    : DotP
    | CrossP
    ;

shiftOperation
    : ShiftLeft
    | ShiftRight
    | ShiftRightLogical
    ;

bitwiseOperation
    : Xor
    | BwAnd
    | Pipe
    ;

/////////////////// reserved ///////////////////

// types
Integer
    : 'int'
    ;
Bool
    : 'bool'
    ;
Char
    : 'char'
    ;
Float
    : 'float'
    ;
Vector
    : 'vector'
    ;

Matrix
    : 'matrix'
    ;

String
    : 'string'
    ;
/*
Tuple : 'tuple'
    ; 
Set 
    : 'set'
    ;
*/

// parenthesis
OpenPar
    : '('
    ;
ClosePar
    : ')'
    ;
OpenBrace
    : '{'
    ;
CloseBrace
    : '}'
    ;
OpenSqr
    : '['
    ;
CloseSqr
    : ']'
    ;
OpenAngle
    : '<'
    ;
CloseAngle
    : '>'
    ;

// control
Function
    : 'func'
    ;
Main
    : 'main'
    ;
Break
    : 'break'
    ;
Continue
    : 'continue'
    ;
Mut
    : 'mut'
    ;
Let
    : 'let'
    ;
Return
    : 'return'
    ;
Returns
    : '->'
    ;
If
    : 'if'
    ;
Else
    : 'else'
    ;
While
    : 'while'
    ;
For
    : 'for'
    ;
Repeat
    : 'repeat'
    ;
Until
    : 'until'
    ;
In
    : 'in'
    ;
As
    : 'as'
    ;
Copy
    : 'copy'
    ;
DeepCopy
    : 'deep_copy'
    ;
Print
    : 'print'
    ;
Size
    : 'size'
    ;
Rows
    : 'rows'
    ;
Cols
    : 'cols'
    ;
Assert
    : 'assert'
    ;
Reverse
    : 'reverse'
    ;

// macros
Null
    : 'null'
    ;
Identity
    : 'identity'
    ;
Typedef
    : 'typedef'
    ;

// ops
ShiftLeft
    : 'shl'
    ;
ShiftRight
    : 'shr'
    ;
ShiftRightLogical
    : 'shrl'
    ;
Pipe
    : '|'
    ;
BwAnd
    : '&'
    ;
BwNot
    : '~'
    ;

Assign
    : '='
    ;
IsEqual
    : '=='
    ;
NotIsEqual
    : '!='
    ;
/* Less
    : OpenAngle
    ; */
LessEqual
    : '<='
    ;
/* Greater
    : CloseAngle
    ; */
GreaterEqual
    : '>='
    ;

Plus
    : '+'
    ;
Minus
    : '-'
    ;
Star
    : '*'
    ;
Div
    : '/'
    ;
Rem
    : '%'
    ;
PipePipe
    : '||'
    ;
Hat
    : '^'
    ;

And
    : 'and'
    ;
Or
    : 'or'
    ;
Xor
    : 'xor'
    ;
Not
    : 'not'
    ;
DotP
    : 'dot'
    ;
CrossP
    : 'cross'
    ;
Modulo
    : 'mod'
    ;

fragment True
    : 'true'
    ;
fragment False
    : 'false'
    ;

Question
    : '?'
    ;
Colon
    : ':'
    ;
Semicolon
    : ';'
    ;
Comma
    : ','
    ;
DoubleQuote
    : '"'
    ;
SingleQuote
    : '\''
    ;

Dot
    : '.'
    ;
DotDot
    : '..'
    ;

// 

fragment BooleanConstant
    : True | False
    ;

fragment IdentifierCharacter
    : Digit | NonDigit
    ;

fragment NonDigit
    : [a-zA-Z_]
    ;

fragment Digit
    : [0-9]
    ;

fragment DecimalConstant
    : Digit+
    ;

fragment BinaryConstant
    : '0b' [0-1]+
    ;

fragment HexConstant
    : '0x' [0-1]+
    ;

fragment FloatConstant
    : Fraction ~'.' Exponent?
    | Digits Exponent
    ;

fragment Fraction
    : Digits? Dot Digits | Digits Dot
    ;

fragment Exponent
    : ('e' | 'E') (Plus | Minus)? Digits
    ;

fragment Digits
    : Digit+
    ;

fragment EscapeSequence
    : '\\' ['"?abfnrtv\\]
    ;
fragment StringCharSequence
    : StringChar+
    ;
fragment StringChar
    : ~['"\\\r\n]
    | EscapeSequence
    | '\\\n' // Added line
    | '\\\r\n'
    ;
// Added line
/* IntType
    : 'i' Digit+
    ; */
CharLiteral
    : SingleQuote StringChar SingleQuote
    ;
StringLiteral
    : DoubleQuote StringCharSequence* DoubleQuote
    ;
IntegerLiteral
    : DecimalConstant
    ;
BooleanLiteral
    : BooleanConstant
    ;
BinaryLiteral
    : BinaryConstant
    ;
HexLiteral
    : BinaryConstant
    ;
FloatLiteral
    : FloatConstant
    ;
Identifier
    : NonDigit+ IdentifierCharacter*
    ;

/////////////////// skip ///////////////////
Whitespace
    : [ \t]+ -> skip
    ;
EOLN
    : ( '\r' '\n'? | '\n') -> skip
    ;
BlockComment
    : '/*' .*? '*/' -> skip
    ;
LineComment
    : '//' ~[\r\n]* -> skip
    ;
