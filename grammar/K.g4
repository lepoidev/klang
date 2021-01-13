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
    : While condition statement               # condLoop
    | For (Mut)? Identifier In expr statement # iteratorLoop
    | Repeat statement Until condition        # untilLoop
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
    | Mut Identifier Assign expr Semicolon            # autoMutDecl
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
    : BooleanLiteral
    | BinaryLiteral
    | IntegerLiteral
    | CharLiteral
    | StringLiteral
    | FloatLiteral
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
    | Plus expr                                             # unaryExpr
    | Minus expr                                            # unaryExpr
    | Not expr                                              # unaryExpr
    //| Rows OpenPar expr ClosePar #rowsExpr | Cols OpenPar expr ClosePar #colsExpr | Size OpenPar
    | left = expr booleanOperation right = expr             # booleanExpr
    | left = expr nonBooleanOperation right = expr          # nonBooleanExpr
    | left = expr bitwiseOperation right = expr             # bitwiseExpr
    | left = expr DotDot right = expr                       # rangeExpr
    | left = expr DotP right = expr                         # dotExpr
    | left = expr CrossP right = expr                       # crossExpr
    | left = expr In right = expr                           # inExpr
    | vectorLiteral                                         # basicExpr
    | tupleLiteral                                          # basicExpr
    | Identifier                                            # identifierExpr
    | functionCall                                          # basicExpr
    ; //| Null                                               #nullExpr

// functions

functionIdentifier
    : Function Identifier parameters (Returns type)?
    ;

functionDeclare
    : functionIdentifier statement
    ;

parameters
    : OpenPar (type Identifier (Comma type Identifier)*)? ClosePar
    ;

arguments
    : OpenPar (expr (Comma expr)*)? ClosePar
    ;

functionCall
    : Identifier arguments  # userFunctionCall
    | builtInFunctionCall   # builtinFunctionCall
    ;

builtInFunctionCall
    : Print OpenPar expr ClosePar       # printExpr
    | Size OpenPar expr ClosePar        # sizeExpr
    | Rows OpenPar expr ClosePar        # rowsExpr
    | Cols OpenPar expr ClosePar        # colsExpr
    | Copy OpenPar expr ClosePar        # copyExpr
    | DeepCopy OpenPar expr ClosePar    # deepcopyExpr
    ;

functionCallStatement
    : functionCall Semicolon
    ;

// type

type
    : modifiedType | vectorType | matrixType
    ;
//| tupleType | setType;
typedecl
    : type
    | Let
    ;

modifiedType
    : baseType | customType
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

// operations  

booleanOperation
    : IsEqual
    | NotIsEqual
    | Less
    | LessEqual
    | Greater
    | GreaterEqual
    | And
    | Or
    ;

nonBooleanOperation
    : Plus
    | Minus
    | Star
    | Div
    | Hat
    | Rem
    | DotP
    | CrossP
    | PipePipe
    ;

bitwiseOperation
    : ShiftLeft
    | ShiftRight
    | ShiftRightLogical
    | Xor
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

Assign
    : '='
    ;
IsEqual
    : '=='
    ;
NotIsEqual
    : '!='
    ;
Less
    : OpenAngle
    ;
LessEqual
    : '<='
    ;
Greater
    : CloseAngle
    ;
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
IntType
    : 'i' Digit+
    ;
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
