/*********************************************
*
*           Andre Leite - 2015250489
*           Lucas Ferreira - 2016243439
*
**********************************************/

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "SyntaxTree.h"
    #include "SymTable.h"

    int yylex(void);
    void yyerror(char *s);

    extern char *yytext;
    extern char *strlit;
    extern int yyleng;
    extern int lineCounter;
    extern int columnCounter;
    extern int fatalities;
    extern int initString;

    Node *root;
    Node *temp;
    Node *temp2;
    Node *temp3;
    Node *temp4;
    Node *topNode;

    int assignError = 0;
    int blocks = 0;
    int canBlock = 0; /* 1 or 0 if used in a if else while statement*/
    char *typeAssign;
    char *blockassign;
%}

%union{
    int col;
    struct uni* loki;
    struct node* newNode;
}

%token BOOL CLASS DOTLENGTH DOUBLE ELSE IF INT PRINT PUBLIC RETURN STATIC STRING VOID WHILE
%token SEMICOLON BLANKID AND STAR ARROW COMMA DIV EQ GE GT LBRACE LE LPAR LSQ LT MINUS MOD NE NOT OR PLUS RBRACE RPAR RSQ XOR LSHIFT RSHIFT
%token <loki> ID RESERVED INTLIT REALLIT STRLIT BOOLLIT UNARY
%token <col> ASSIGN PARSEINT

%type  <newNode> Program Declarations FieldDecl Type MethodInvocation MethodDecl MethodHeader
%type  <newNode> MethodAux MethodInvocAux2 MethodInvocAux MethodBody ParseArgs ParametersAux StatementAux1 StatementAux2 StatementAux3
%type  <newNode> FormalParams Expr Statement VarDecl Assignment CommaIDaux Expr1 CommaIDaux2

%left  COMMA
%right ASSIGN
%left  OR
%left  AND
%left  XOR
%left  EQ NE
%left  LT LE GT GE
%left  LSHIFT RSHIFT
%left  PLUS MINUS
%left  STAR DIV MOD
%left  UNARY
%left  LPAR LSQ RPAR RSQ ARROW
%nonassoc ELSE
%nonassoc IF

%%


Program:          CLASS ID LBRACE Declarations RBRACE    {if(fatalities==0){$$ = initNode("NULL","Program",lineCounter,(int)(columnCounter-yyleng));temp = initNode($2->id,"Id",lineCounter,$2->column);addChild($$,temp);addChild($$,$4);root = $$;};}
                ;

Declarations:     MethodDecl Declarations                {if(fatalities==0){$$ = initNode("NULL","MethodDecl",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addSibling($$,$2);};}
                | FieldDecl Declarations                 {if(fatalities==0){$$ = initNode("NULL","FieldDeclTop",lineCounter,(int)(columnCounter-yyleng));addSibling($$,$1);addSibling($$,$2);};}
                | SEMICOLON Declarations                 {if(fatalities==0){$$ = initNode("NULL","SEMICOLON",lineCounter,(int)(columnCounter-yyleng));addSibling($$,$2);};}
                | /*empty*/                              {$$ = NULL;}
                ;


MethodDecl:       PUBLIC STATIC MethodHeader MethodBody  {if(fatalities==0){$$ = initNode("NULL","MethodHeader",lineCounter,(int)(columnCounter-yyleng));addChild($$,$3);addSibling($$,$4);};}
                ;

FieldDecl:        PUBLIC STATIC Type ID CommaIDaux2 SEMICOLON {if(fatalities==0){$$ = initNode("NULL","FieldDecl",lineCounter,(int)(columnCounter-yyleng));temp = $3;addChild($$,temp);temp2 = initNode($4->id,"Id",lineCounter,$4->column);addSibling(temp,temp2);addSibling($$,$5);};}
                | error SEMICOLON                        {$$ = NULL;}
                ;

CommaIDaux2:       COMMA ID CommaIDaux2                  {if(fatalities==0){$$ = initNode("NULL","FieldDecl",lineCounter,(int)(columnCounter-yyleng));temp3=initNode("NULL",typeAssign,lineCounter,(int)(columnCounter-yyleng));addChild($$,temp3);temp4 = initNode($2->id,"Id",lineCounter,$2->column);addSibling(temp3,temp4);addSibling($$,$3);};}
                | /*empty*/                              {$$ = NULL;}
                ;

Type:             BOOL                                   {$$ = initNode("NULL","Bool",lineCounter,(int)(columnCounter-yyleng));typeAssign=strdup("Bool");}
                | INT                                    {$$ = initNode("NULL","Int",lineCounter,(int)(columnCounter-yyleng));typeAssign=strdup("Int");}
                | DOUBLE                                 {$$ = initNode("NULL","Double",lineCounter,(int)(columnCounter-yyleng));typeAssign=strdup("Double");}
                ;

MethodHeader:     Type ID LPAR FormalParams RPAR         {if(fatalities==0){$$ = $1;temp = initNode($2->id,"Id",lineCounter,$2->column);addSibling($$,temp);temp2 = initNode("NULL","MethodParams",lineCounter,(int)(columnCounter-yyleng));addSibling($$,temp2);addChild(temp2,$4);};}
                | VOID ID LPAR FormalParams RPAR         {if(fatalities==0){$$ = initNode("NULL","Void",lineCounter,(int)(columnCounter-yyleng));temp = initNode($2->id,"Id",lineCounter,$2->column);addSibling($$,temp);temp2 = initNode("NULL","MethodParams",lineCounter,(int)(columnCounter-yyleng));addSibling($$,temp2);addChild(temp2,$4);};}
                | VOID ID LPAR RPAR                      {if(fatalities==0){$$ = initNode("NULL","Void",lineCounter,(int)(columnCounter-yyleng));temp = initNode($2->id,"Id",lineCounter,$2->column);addSibling($$,temp);temp2 = initNode("NULL","MethodParams",lineCounter,(int)(columnCounter-yyleng));addSibling($$,temp2);};}
                | Type ID LPAR RPAR                      {if(fatalities==0){$$ = $1;temp = initNode($2->id,"Id",lineCounter,$2->column);addSibling($$,temp);temp2 = initNode("NULL","MethodParams",lineCounter,(int)(columnCounter-yyleng));addSibling($$,temp2);};}
                ;

FormalParams:     Type ID ParametersAux                  {if(fatalities==0){$$ = initNode("NULL","ParamDecl",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);temp = initNode($2->id,"Id",lineCounter,$2->column);addChild($$,temp);addSibling($$,$3);};}
                | STRING LSQ RSQ ID                      {if(fatalities==0){$$ = initNode("NULL","ParamDecl",lineCounter,(int)(columnCounter-yyleng));temp2 = initNode("NULL","StringArray",lineCounter,(int)(columnCounter-yyleng));addChild($$,temp2);temp = initNode($4->id,"Id",lineCounter,$4->column);addChild($$,temp);};}
                ;

ParametersAux:    COMMA Type ID ParametersAux            {if(fatalities==0){$$ = initNode("NULL","ParamDecl",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);temp = initNode($3->id,"Id",lineCounter,$3->column);addChild($$,temp);addSibling($$,$4);};}
                | /*empty*/                              {$$ = NULL;}
                ;


MethodBody:       LBRACE MethodAux RBRACE                {if(fatalities==0){$$ = initNode("NULL","MethodBody",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);}}
                ;

MethodAux:        Statement MethodAux                    {if(fatalities==0){topNode = NULL;$$ = initNode("NULL","MethodAuxTop",lineCounter,(int)(columnCounter-yyleng));addSibling($$,$1);addSibling($$,$2);};}
                | VarDecl MethodAux                      {if(fatalities==0){topNode = NULL;$$ = initNode("NULL","VarDeclTop",lineCounter,(int)(columnCounter-yyleng));addSibling($$,$1);addSibling($$,$2);};}
                | /*empty*/                              {$$ = NULL;}
                ;

VarDecl:          Type ID CommaIDaux SEMICOLON           {if(fatalities==0){$$ = initNode("NULL","VarDecl",lineCounter,(int)(columnCounter-yyleng));temp = $1;addChild($$,temp);temp2 = initNode($2->id,"Id",lineCounter,$2->column);addSibling(temp,temp2);addSibling($$,$3);};}
                ;

CommaIDaux:       COMMA ID CommaIDaux                    {if(fatalities==0){$$ = initNode("NULL","VarDecl",lineCounter,(int)(columnCounter-yyleng));temp3=initNode("NULL",typeAssign,lineCounter,(int)(columnCounter-yyleng));addChild($$,temp3);temp4 = initNode($2->id,"Id",lineCounter,$2->column);addSibling(temp3,temp4);addSibling($$,$3);};}
                | /*empty*/                              {$$ = NULL;}
                ;


Statement:        LBRACE StatementAux1 RBRACE            {if(fatalities==0){if($2 != NULL && $2->sibling != NULL){$$=initNode("NULL","Block",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);}else{$$=$2;}};}
                | IF LPAR Expr RPAR Statement            {if(fatalities==0){$$=initNode("NULL","If",lineCounter,(int)(columnCounter-yyleng));addChild($$, $3);if($5 != NULL){addChild($$, $5);}else{temp2=initNode("NULL","Block",lineCounter,(int)(columnCounter-yyleng));addChild($$,temp2);};temp = initNode("NULL", "Block",lineCounter,(int)(columnCounter-yyleng));addChild($$, temp);};}
                | IF LPAR Expr RPAR Statement ELSE Statement      {if(fatalities==0){$$=initNode("NULL","If",lineCounter,(int)(columnCounter-yyleng));addChild($$, $3);if($5 != NULL){addChild($$, $5);}else{temp2=initNode("NULL","Block",lineCounter,(int)(columnCounter-yyleng));addChild($$,temp2);};if($7 != NULL){addChild($$,$7);}else{temp3=initNode("NULL","Block",lineCounter,(int)(columnCounter-yyleng));addChild($$,temp3);};};}
                | WHILE LPAR Expr RPAR Statement         {if(fatalities==0){$$=initNode("NULL","While",lineCounter,(int)(columnCounter-yyleng));addChild($$,$3);if($5==NULL){temp=initNode("NULL","Block",lineCounter,(int)(columnCounter-yyleng));addChild($$,temp);}else{addChild($$,$5);};};}
                | RETURN StatementAux2 SEMICOLON         {if(fatalities==0){$$=initNode("NULL","Return",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);};}
                | StatementAux3 SEMICOLON                {if(fatalities==0){$$=$1;};}
                | PRINT LPAR STRLIT RPAR SEMICOLON       {if(fatalities==0){$$=initNode("NULL","Print",lineCounter,(int)(columnCounter-yyleng));temp=initNode($3->id,"StrLit",lineCounter,$3->column);addChild($$,temp);};}
                | PRINT LPAR Expr RPAR SEMICOLON         {if(fatalities==0){$$=initNode("NULL","Print",lineCounter,(int)(columnCounter-yyleng));addChild($$,$3);};}
                | error SEMICOLON                        {$$ = NULL;}
                ;

StatementAux1:    Statement StatementAux1               {if(fatalities==0){if($1 != NULL && $2 != NULL){$$ = $1;addSibling($$, $2);}else if($1 == NULL){$$ = $2;}else if($2 == NULL){$$ = $1;};};}
                | /*empty*/                              {$$=NULL;}
                ;

StatementAux2:    Expr                                   {if(fatalities==0){$$=$1;};}
                | /*empty*/                              {$$=NULL;}
                ;

StatementAux3:    MethodInvocation                       {if(fatalities==0){$$=initNode("NULL","Call",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);$$->column=1;};}
                | Assignment                             {if(fatalities==0){$$=initNode("NULL","Assign",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);};}
                | ParseArgs                              {if(fatalities==0){$$=initNode("NULL","ParseArgs",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);};}
                | /*empty*/                              {$$=NULL;}
                ;

MethodInvocation: ID LPAR MethodInvocAux RPAR            {if(fatalities==0){$$ = initNode($1->id,"Id",lineCounter,$1->column);addSibling($$,$3);};}
                | ID LPAR error RPAR                     {$$ = NULL;}
                ;

MethodInvocAux:   Expr MethodInvocAux2                   {if(fatalities==0){$$=$1;addSibling($$,$2);};}
                | /*empty*/                              {$$ = NULL;}
                ;

MethodInvocAux2:  COMMA Expr MethodInvocAux2             {if(fatalities==0){$$=$2;addSibling($$,$3);};}
                | /*empty*/                              {$$ = NULL;}
                ;

Assignment:       ID ASSIGN Expr                         {if(fatalities==0){$$ = initNode($1->id,"Id",lineCounter,$1->column);$$->column = $2;addSibling($$,$3);};}
                ;

ParseArgs:        PARSEINT LPAR ID LSQ Expr RSQ RPAR     {if(fatalities==0){$$ = initNode($3->id,"Id",lineCounter,$3->column);$$->column = $1;addSibling($$,$5);};}
                | PARSEINT LPAR error RPAR               {$$ = NULL;}
                ;

Expr:             Expr1                                  {if(fatalities==0){$$=$1;};}
                | Assignment                             {if(fatalities==0){$$=initNode("NULL","Assign",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);};}
                ;

Expr1:            Expr1 AND Expr1                        {if(fatalities==0){$$=initNode("NULL","And",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 OR Expr1                         {if(fatalities==0){$$=initNode("NULL","Or",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 XOR Expr1                        {if(fatalities==0){$$=initNode("NULL","Xor",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 STAR  Expr1                      {if(fatalities==0){$$=initNode("NULL","Mul",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 DIV  Expr1                       {if(fatalities==0){$$=initNode("NULL","Div",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 MOD  Expr1                       {if(fatalities==0){$$=initNode("NULL","Mod",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 LSHIFT Expr1                     {if(fatalities==0){$$=initNode("NULL","Lshift",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 RSHIFT Expr1                     {if(fatalities==0){$$=initNode("NULL","Rshift",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 PLUS  Expr1                      {if(fatalities==0){$$=initNode("NULL","Add",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 MINUS  Expr1                     {if(fatalities==0){$$=initNode("NULL","Sub",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 EQ Expr1                         {if(fatalities==0){$$=initNode("NULL","Eq",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 NE Expr1                         {if(fatalities==0){$$=initNode("NULL","Ne",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 GE Expr1                         {if(fatalities==0){$$=initNode("NULL","Ge",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 GT Expr1                         {if(fatalities==0){$$=initNode("NULL","Gt",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 LE Expr1                         {if(fatalities==0){$$=initNode("NULL","Le",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | Expr1 LT Expr1                         {if(fatalities==0){$$=initNode("NULL","Lt",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);addChild($$,$3);};}
                | MINUS Expr1 %prec UNARY                {if(fatalities==0){$$=initNode("NULL", "Minus",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);};}
                | NOT Expr1 %prec UNARY                  {if(fatalities==0){$$=initNode("NULL", "Not",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);};}
                | PLUS Expr1 %prec UNARY                 {if(fatalities==0){$$=initNode("NULL", "Plus",lineCounter,(int)(columnCounter-yyleng));addChild($$,$2);};}
                | LPAR Expr RPAR                         {if(fatalities==0){$$=$2;};}
                | MethodInvocation                       {if(fatalities==0){$$=initNode("NULL","Call",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);};}
                | ParseArgs                              {if(fatalities==0){$$=initNode("NULL","ParseArgs",lineCounter,(int)(columnCounter-yyleng));addChild($$,$1);};}
                | ID DOTLENGTH                           {if(fatalities==0){$$=initNode("NULL","Length",lineCounter,(int)(columnCounter-yyleng));temp=initNode($1->id,"Id",lineCounter,$1->column);addChild($$,temp);};}
                | ID                                     {if(fatalities==0){$$=initNode($1->id,"Id",lineCounter,$1->column);};}
                | INTLIT                                 {if(fatalities==0){$$=initNode($1->id,"DecLit",lineCounter,$1->column);};}
                | REALLIT                                {if(fatalities==0){$$=initNode($1->id,"RealLit",lineCounter,$1->column);};}
                | BOOLLIT                                {if(fatalities==0){$$=initNode($1->id,"BoolLit",lineCounter,$1->column);};}
                | LPAR error RPAR                        {$$ = NULL;}
                ;

%%

void yyerror(char *s)
{
    printf("Line %d, col %d: %s: %s\n", lineCounter, (int)(columnCounter-strlen(yytext)) , s, yytext);
    fatalities = 1;
}