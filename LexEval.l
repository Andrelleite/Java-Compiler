/********************************************************
*  André Leite , 2015250489 , uc2015250489@student.uc.pt
*
*			LEXICAL ANALYZER - META 1
*			   COMPILADORES 18/19
*********************************************************/

%option yylineno
%{

char id[256];
char token[10240][256];
char strtook[1024];
int dig = 0;
int lines = 1;
int columns = 1;
int comcount = 0;
int len = 0;
int comCol = 1;
int comLine = 1;
int strCol = 1;
int strLine = 1;
int escCol = 1;
int escLine = 1;
int errors = 0;
int MinusL = 0;

void print_tokens(){

	int len = dig;
	int i;
	for(i = 0; i < len; i++){
		printf("%s\n",token[i]);
	}

}

void check_erros(){


	if(errors == 0 && MinusL == 1){
		sprintf(token[dig],"STRLIT(\"%s\")",strtook);
		dig++;
	}
	memset(&strtook[0], 0, sizeof(strtook));

}



%}

PACKAGE				"package"
RETURN				"return"
FOR					"for"
SEMICOLON			";"
BLANKID				"_"
AND 				"&&"
ASSIGN 				"="
STAR				"*"
COMMA				","
DIVISION			"/"
EQ					"=="
GE					">="
GT					">"
LBRACE				"{"
LE					"<="
LPAR				"("
LSQ					"["
LT					"<"
MINUS				"-"
MOD					"%"
NE					"!="
NOT					"!"
OR					"||"
PLUS				"+"
RBRACE				"}"
RPAR				")"
RSQ					"]"
ELSE				"else"
IF					"if"
VAR					"var"
INT 				"int"
FLOAT32				"float32"
BOOL				"bool"
STRING				"string"
PRINT				"fmt.Println"
PARSEINT			"strconv.Atoi"
FUNC				"func"
CMDARGS				"os.Args"
RESERVED			"break"|"default"|"func"|"interface","select","case"|"defer"|"go"|"map"|"struct"|"chan"|"else"|"goto"|"package"|"switch"|"const"|"fallthrough"|"if"|"range"|"type"|"continue"|"for"|"import"|"return"|"var"|"++"|"--"
INTLIT				(0?[0-9]+)|(0x|0X)([0-9]|[a-fA-F])+
REALLIT				([0-9]+"."(([0-9]+)?(("e"|"E")("+"|"-")?[0-9]+)?))|("."[0-9]+((("e"|"E")("+"|"-")?[0-9]+)?))|([0-9]+(("e"|"E")("+"|"-")?[0-9]+))
ID 					([a-zA-Z]|"_")([a-zA-Z]|[0-9]|"_")*

%X MUTLI
%X LINE
%X STRLIT ESCAPES


%%

\"					{BEGIN STRLIT; strLine = lines; strCol = columns++;errors = 0;}
<STRLIT>\"			{columns += yyleng;check_erros();errors=0;BEGIN 0;}
<STRLIT>\\			{BEGIN ESCAPES; escLine = lines; escCol = columns; strcat(strtook,yytext);columns++;}
<ESCAPES>"t"		{columns++;strcat(strtook,yytext);BEGIN STRLIT;}
<ESCAPES>"f"		{columns++;strcat(strtook,yytext);BEGIN STRLIT;}
<ESCAPES>"n"		{columns++;strcat(strtook,yytext);BEGIN STRLIT;}
<ESCAPES>"r"		{columns++;strcat(strtook,yytext);BEGIN STRLIT;}
<ESCAPES>\"			{columns++;strcat(strtook,yytext);BEGIN STRLIT;}
<ESCAPES>\\			{columns++;strcat(strtook,yytext);BEGIN STRLIT;}
<ESCAPES>.			{columns++;memset(&strtook[0], 0, sizeof(strtook));sprintf(token[dig],"Line %d, column %d: invalid escape sequence (\\%s)",escLine,escCol,yytext);errors++;dig++;BEGIN STRLIT;}
<STRLIT>.			{columns+=yyleng;strcat(strtook,yytext);}
<STRLIT>\n			{errors++;sprintf(token[dig],"Line %d, column %d: unterminated string literal",strLine,strCol);dig++;check_erros();memset(&strtook[0], 0, sizeof(strtook));columns=1;lines++;BEGIN 0;}
<STRLIT><<EOF>>		{errors++;sprintf(token[dig],"Line %d, column %d: unterminated string literal",strLine,strCol);dig++;check_erros();return 0;}

"/*"				{BEGIN MUTLI; comLine = lines; comCol = columns;}
<MUTLI>"*/"			{BEGIN 0;columns += yyleng;}
<MUTLI>.			{columns++;}
<MUTLI>\n			{columns = 1;lines++;}
<MUTLI><<EOF>>		{sprintf(token[dig],"Line %d, column %d: unterminated comment", comLine, comCol);dig++; return 0;}

"//"				{BEGIN LINE; comLine = lines; comCol = columns;}
<LINE>.				{columns++;}
<LINE>\n			{lines++;columns=1;BEGIN 0;if(MinusL==1){strcpy(token[dig],"NEWLINE");}}
<LINE><<EOF>>		{sprintf(token[dig],"Line %d, column %d: unterminated comment", comLine, comCol);dig++;if(MinusL==1){strcpy(token[dig],"NEWLINE");} return 0;}

{PACKAGE}			{if(MinusL==1){strcpy(token[dig],"PACKAGE");dig++;}columns+=strlen(yytext);}
{FOR}				{if(MinusL==1){strcpy(token[dig],"FOR");dig++;}columns+=strlen(yytext);}
{RETURN}			{if(MinusL==1){strcpy(token[dig],"RETURN");dig++;}columns+=strlen(yytext);}
{SEMICOLON}			{if(MinusL==1){strcpy(token[dig],"SEMICOLON");dig++;}columns+=strlen(yytext);}
{BLANKID}			{if(MinusL==1){strcpy(token[dig],"BLANKID");dig++;}columns+=strlen(yytext);}
{AND}				{if(MinusL==1){strcpy(token[dig],"AND");dig++;}columns+=strlen(yytext);}
{ASSIGN}			{if(MinusL==1){strcpy(token[dig],"ASSIGN");dig++;}columns+=strlen(yytext);}
{STAR}				{if(MinusL==1){strcpy(token[dig],"STAR");dig++;}columns+=strlen(yytext);}
{COMMA}				{if(MinusL==1){strcpy(token[dig],"COMMA");dig++;}columns+=strlen(yytext);}
{DIVISION}			{if(MinusL==1){strcpy(token[dig],"DIVISION");dig++;}columns+=strlen(yytext);}
{EQ}				{if(MinusL==1){strcpy(token[dig],"EQ");dig++;}columns+=strlen(yytext);}
{GE}				{if(MinusL==1){strcpy(token[dig],"GE");dig++;}columns+=strlen(yytext);}
{GT}				{if(MinusL==1){strcpy(token[dig],"GT");dig++;}columns+=strlen(yytext);}
{LBRACE}			{if(MinusL==1){strcpy(token[dig],"LBRACE");dig++;}columns+=strlen(yytext);}
{LE}				{if(MinusL==1){strcpy(token[dig],"LE");dig++;}columns+=strlen(yytext);}
{LPAR}				{if(MinusL==1){strcpy(token[dig],"LPAR");dig++;}columns+=strlen(yytext);}
{LSQ}				{if(MinusL==1){strcpy(token[dig],"LSQ");dig++;}columns+=strlen(yytext);}
{LT}				{if(MinusL==1){strcpy(token[dig],"LT");dig++;}columns+=strlen(yytext);}
{MINUS}				{if(MinusL==1){strcpy(token[dig],"MINUS");dig++;}columns+=strlen(yytext);}
{MOD}				{if(MinusL==1){strcpy(token[dig],"MOD");dig++;}columns+=strlen(yytext);}
{NE}				{if(MinusL==1){strcpy(token[dig],"NE");dig++;}columns+=strlen(yytext);}
{NOT}				{if(MinusL==1){strcpy(token[dig],"NOT");dig++;}columns+=strlen(yytext);}
{OR}				{if(MinusL==1){strcpy(token[dig],"OR");dig++;}columns+=strlen(yytext);}
{PLUS}				{if(MinusL==1){strcpy(token[dig],"PLUS");dig++;}columns+=strlen(yytext);}
{RBRACE}			{if(MinusL==1){strcpy(token[dig],"RBRACE");dig++;}columns+=strlen(yytext);}
{RPAR}				{if(MinusL==1){strcpy(token[dig],"RPAR");dig++;}columns+=strlen(yytext);}
{RSQ}				{if(MinusL==1){strcpy(token[dig],"RSQ");dig++;}columns+=strlen(yytext);}
{ELSE}				{if(MinusL==1){strcpy(token[dig],"ELSE");dig++;}columns+=strlen(yytext);}
{IF}				{if(MinusL==1){strcpy(token[dig],"IF");dig++;}columns+=strlen(yytext);}
{VAR}				{if(MinusL==1){strcpy(token[dig],"VAR");dig++;}columns+=strlen(yytext);}
{INT}				{if(MinusL==1){strcpy(token[dig],"INT");dig++;}columns+=strlen(yytext);}
{FLOAT32}			{if(MinusL==1){strcpy(token[dig],"FLOAT32");dig++;}columns+=strlen(yytext);}
{BOOL}				{if(MinusL==1){strcpy(token[dig],"BOOL");dig++;}columns+=strlen(yytext);}
{STRING}			{if(MinusL==1){strcpy(token[dig],"STRING");dig++;}columns+=strlen(yytext);}
{PRINT}				{if(MinusL==1){strcpy(token[dig],"PRINT");dig++;}columns+=strlen(yytext);}
{PARSEINT}			{if(MinusL==1){strcpy(token[dig],"PARSEINT");dig++;}columns+=strlen(yytext);}
{FUNC}				{if(MinusL==1){strcpy(token[dig],"FUNC");dig++;}columns+=strlen(yytext);}
{CMDARGS}			{if(MinusL==1){strcpy(token[dig],"CMDARGS");dig++;}columns+=strlen(yytext);}
{ID}				{if(MinusL==1){sprintf(token[dig],"ID(%s)",yytext);dig++;}columns+=strlen(yytext);}
{RESERVED} 			{if(MinusL==1){strcpy(token[dig],"RESERVED");dig++;}columns+=strlen(yytext);}
{INTLIT}			{if(MinusL==1){sprintf(token[dig],"INTLIT(%s)",yytext);dig++;}columns+=strlen(yytext);}
{REALLIT}			{if(MinusL==1){sprintf(token[dig],"REALLIT(%s)",yytext);dig++;}columns+=strlen(yytext);}
\n					{if(MinusL==1){strcpy(token[dig],"NEWLINE");}lines++;columns=1;}
" "|"\t"			{columns+=yyleng;}
\r|\n\r				;
.					{sprintf(token[dig],"Line %d, column %d: illegal character (%s)",lines,columns,yytext);dig++;columns++;}

%%

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv ){

	for (int j = 0; j < argc; j++){
		if(strcmp(argv[j], "-l") == 0){
			MinusL = 1;
		}
	}
	yylex();
	print_tokens();
	return 0;
}



int yywrap(){
	return 1;
}