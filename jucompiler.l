/*********************************************
*
*           Andre Leite - 2015250489
*           Lucas Ferreira - 2016243439
*
**********************************************/

%option	yylineno
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <ctype.h>
  #include <locale.h>
  #include "y.tab.h"
  #include "SyntaxTree.h"
  #include "SymTable.h"


  int l = 0;
  int e1 = 0;
  int e2 = 0;
  int s1 = 0;
  int lineCounter = 1;
  int lineOpCounter = 0;
  int columnCounter = 1;
  int strtoken = 0;
  int terminated = 0;
  int initString = 0;
  int initline =0;
  int error = 0;
  int semantics = 0;

  char *line[25];
  char strlit[250];
  char toend[250];
  int fatalities=0;

  extern Node *root;

  void updateArray(char* input){
      line[lineOpCounter]=input;
      lineOpCounter++;
  }

  void printStrlit(){
      if(strlit[0]!='\"'){
          return;
      }
      else{
          if(l == 1){
              printf("STRLIT(%s)\n",strlit);
          }
          strtoken=0;
          memset(strlit,0,sizeof(strlit));
      }
  }

  int checkTerminated(){
      int aAspas=0;
      int fAspas=0;
      for(int i=0;i<lineOpCounter;i++){
          if(strcmp(line[i],"fecha-aspas")==0){
              fAspas++;
          }
          if(strcmp(line[i],"abre-aspa")==0){
              aAspas++;
          }
      }
      if(aAspas==fAspas){
          return 1;
      }
      else{
          memset(strlit,0,sizeof(strlit));
          return 0;
      }
  }
  
  void makepacket(int col, char *t){
    yylval.loki = (Uni *)malloc(sizeof(Uni));
    yylval.loki->id = strdup(t);
    yylval.loki->column = col-strlen(t);
  }

%}

%X LINE_COMMENT COMMENT ESCAPE ESCAPE_STR STR

blankid						             "_"+
letter                         [a-z]|[A-Z]|{blankid}|"$"
zero                           0
decimal                        [0-9]+
rightdecimal                   [0-9]+("_"*[0-9]+)*

reallit                		     ({intlitzero}+"."(({intlitzero}+)?(("e"|"E")("+"|"-")?{intlitzero}+)?))|("."{intlitzero}+((("e"|"E")("+"|"-")?{intlitzero}+)?))|({intlitzero}+(("e"|"E")("+"|"-")?{intlitzero}+))
id 					                   ([a-zA-Z]|"_"|"$")([a-zA-Z]|[0-9]|"_"|"$")*
intlit 						             [1-9]+|[1-9]([0-9]*"_"*)*[0-9]+
intlitzero   				           [0-9]+|[0-9]([0-9]*"_"*)*[0-9]+

ASC                            [\x00-\x7f]
ASCN                           [\x00-\t\v-\x7f]
U                              [\x80-\xbf]
U2                             [\xc2-\xdf]
U3                             [\xe0-\xef]
U4                             [\xf0-\xf4]
UANY                           {ASC}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UANYN                          {ASCN}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UONLY                          {U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}

boollit                        true|false
and                            "&&"
assign                         "="
star                           "*"
comma                          ","
div                            "/"
great                          ">"
lbrace                         "{"
less                           "<"
lpar                           "("
lsq                            "["
minus                          "-"
mod                            "%"
not                            "!"
or                             "||"
plus                           "+"
rbrace                         "}"
rpar                           ")"
rsq                            "]"
semicolon                      ";"
xor                            "^"

bool                           boolean
class                          class
dotlength                      "."length
double                         double
else                           else
if                             if
int                            int
print                          System"."out"."print
parseint                       Integer"."parseInt
public                         public
return                         return
static                         static
string                         String
void                           void
while                          while
nullito
reserved                       "++"|"--"|default|do|double|else|enum|extends|false|final|finally|float|for|goto|if|implements|import|instanceof|int|interface|long|native|new|null|package|private|protected|public|return|short|static|strictfp|super|switch|synchronized|this|throw|throws|transient|true|try|void|volatile|while|continue|null|Integer|System|byte|case|catch|char|enum|final|float|implements|import|long|native|new|package|protected|return|short|static|super|this|transient|volatile|void|break|assert|abstract|const
%%

"//"                           {columnCounter+=yyleng;BEGIN LINE_COMMENT;}
<LINE_COMMENT>\n|\r|\r\n       {columnCounter=1;BEGIN 0;lineCounter++;}
<LINE_COMMENT>.                {columnCounter+=yyleng;}

"/*"                           {initline = lineCounter; initString = columnCounter;columnCounter+=yyleng;BEGIN COMMENT;}
<COMMENT>\n|\r|\r\n            {columnCounter=1;lineCounter++;}
<COMMENT>.                     {columnCounter+=yyleng;}
<COMMENT><<EOF>>               {printf("Line %d, col %d: unterminated comment\n",initline,initString);initString=0;initline=0;BEGIN 0;}
<COMMENT>"*/"                  {columnCounter+=yyleng;BEGIN 0;}

"\""                           {memset(strlit,0,sizeof(strlit));updateArray("abre-aspa");strcat(strlit,yytext);initString=columnCounter;columnCounter+=yyleng;error=0;BEGIN STR;}
<STR>\\                        {strcat(strlit,yytext);BEGIN ESCAPE_STR;}
<STR>\"                        {columnCounter+=yyleng;strcat(strlit,yytext);updateArray("fecha-aspas");yylval.loki = malloc(sizeof(Uni));if(error!=1){if(l==-1){yylval.loki->id = strdup(strlit);yytext=strdup(yylval.loki->id );error=0;BEGIN 0;yylval.loki->column =columnCounter-strlen(strlit);return STRLIT;}else{printStrlit();};}else{memset(strlit,0,sizeof(strlit));};error=0;BEGIN 0;}
<STR>\n|\r|\r\n                {columnCounter+=yyleng;terminated=checkTerminated();if(terminated == 0 && e1 == 1){printf("Line %d, col %d: unterminated string literal\n",lineCounter,initString);};lineCounter++;columnCounter=1;lineOpCounter=0;BEGIN 0;}
<STR><<EOF>>                   {columnCounter+=yyleng;terminated=checkTerminated();if(e1 == 1){printf("Line %d, col %d: unterminated string literal\n",lineCounter,initString);};lineCounter++;lineOpCounter=0;BEGIN 0;}
<STR>.                         {columnCounter+=yyleng;strcat(strlit,yytext);}

<ESCAPE_STR>"f"                {columnCounter+=yyleng+1;strcat(strlit,yytext);BEGIN STR;}
<ESCAPE_STR>"n"                {columnCounter+=yyleng+1;strcat(strlit,yytext);BEGIN STR;}
<ESCAPE_STR>"r"                {columnCounter+=yyleng+1;strcat(strlit,yytext);BEGIN STR;}
<ESCAPE_STR>"t"                {columnCounter+=yyleng+1;strcat(strlit,yytext);BEGIN STR;}
<ESCAPE_STR>"\\"               {columnCounter+=yyleng+1;strcat(strlit,yytext);BEGIN STR;}
<ESCAPE_STR>\"                 {columnCounter+=yyleng+1;strcat(strlit,yytext);BEGIN STR;}
<ESCAPE_STR>\n|\r|\r\n         {if(e1 == 1){printf("Line %d, col %d: invalid escape sequence (\\%s)\n",lineCounter,columnCounter,"");};terminated=checkTerminated();if(terminated == 0 && e1 == 1 && l != -1){printf("Line %d, col %d: unterminated string literal\n",lineCounter,initString);};error=1;memset(strlit,0,sizeof(strlit));lineCounter++;columnCounter=1;lineOpCounter=0;BEGIN 0;}
<ESCAPE_STR>.                  {strcat(strlit,yytext);if(e1 == 1){printf("Line %d, col %d: invalid escape sequence (\\%s)\n",lineCounter,columnCounter,yytext);};columnCounter+=yyleng+1;error=1;BEGIN STR;}

{reallit}		   	               {if(l==1){printf("REALLIT(%s)\n", yytext);};columnCounter+=yyleng;updateArray("reallit");if(l == -1){makepacket(columnCounter,yytext); return REALLIT;};}
{intlit}		      		         {if(l==1){printf("INTLIT(%s)\n", yytext);};columnCounter+=yyleng;updateArray("intlit");if(l == -1){makepacket(columnCounter,yytext); return INTLIT;};}
{zero}                         {if(l==1){printf("INTLIT(%s)\n", yytext);};columnCounter+=yyleng;updateArray("intlit");if(l == -1){makepacket(columnCounter,yytext); return INTLIT;};}
{boollit}                      {if(l==1){printf("BOOLLIT(%s)\n",yytext);};columnCounter+=yyleng;updateArray("boollit");if(l == -1){makepacket(columnCounter,yytext); return BOOLLIT;};}
{and}                          {if(l==1){printf("AND\n");};columnCounter+=yyleng;updateArray("and");if(l == -1){return AND;};}
{assign}                       {if(l==1){printf("ASSIGN\n");};columnCounter+=yyleng;updateArray("assign");if(l == -1){yylval.col = columnCounter-yyleng;return ASSIGN;};}
{star}                         {if(l==1){printf("STAR\n");};columnCounter+=yyleng;updateArray("star");if(l == -1){return STAR;};}
{comma}                        {if(l==1){printf("COMMA\n");};columnCounter+=yyleng;updateArray("comma");if(l == -1){return COMMA;};}
{div}                          {if(l==1){printf("DIV\n");};columnCounter+=yyleng;updateArray("div");if(l == -1){return DIV;};}
{assign}{assign}               {if(l==1){printf("EQ\n");};columnCounter+=yyleng;updateArray("eq");if(l == -1){return EQ;};}
{great}{assign}                {if(l==1){printf("GE\n");};columnCounter+=yyleng;updateArray("ge");if(l == -1){return GE;};}
{great}                        {if(l==1){printf("GT\n");};columnCounter+=yyleng;updateArray("gt");if(l == -1){return GT;};}
{lbrace}                       {if(l==1){printf("LBRACE\n");};columnCounter+=yyleng;updateArray("lbrace");if(l == -1){return LBRACE;};}
{less}{assign}                 {if(l==1){printf("LE\n");};columnCounter+=yyleng;updateArray("le");if(l == -1){return LE;};}
{lpar}                         {if(l==1){printf("LPAR\n");};columnCounter+=yyleng;updateArray("lpar");if(l == -1){return LPAR;};}
{lsq}                          {if(l==1){printf("LSQ\n");};columnCounter+=yyleng;updateArray("lsq");if(l == -1){return LSQ;};}
{less}                         {if(l==1){printf("LT\n");};columnCounter+=yyleng;updateArray("less");if(l == -1){return LT;};}
{minus}                        {if(l==1){printf("MINUS\n");};columnCounter+=yyleng;updateArray("minus");if(l == -1){return MINUS;};}
{mod}                          {if(l==1){printf("MOD\n");};columnCounter+=yyleng;updateArray("mod");if(l == -1){return MOD;};}
{not}{assign}                  {if(l==1){printf("NE\n");};columnCounter+=yyleng;updateArray("ne");if(l == -1){return NE;};}
{not}                          {if(l==1){printf("NOT\n");};columnCounter+=yyleng;updateArray("not");if(l == -1){return NOT;};}
{or}                           {if(l==1){printf("OR\n");};columnCounter+=yyleng;updateArray("or");if(l == -1){return OR;};}
{plus}                         {if(l==1){printf("PLUS\n");};columnCounter+=yyleng;updateArray("plus");if(l == -1){return PLUS;};}
{rbrace}                       {if(l==1){printf("RBRACE\n");};columnCounter+=yyleng;updateArray("rbrace");if(l == -1){return RBRACE;};}
{rpar}                         {if(l==1){printf("RPAR\n");};columnCounter+=yyleng;updateArray("rpar");if(l == -1){return RPAR;};}
{rsq}                          {if(l==1){printf("RSQ\n");};columnCounter+=yyleng;updateArray("rsq");if(l == -1){return RSQ;};}
{semicolon}					           {if(l==1){printf("SEMICOLON\n");};columnCounter+=yyleng;updateArray("semicolon");memset(strlit,0,sizeof(strlit));if(l == -1){return SEMICOLON;};}
{minus}{great}                 {if(l==1){printf("ARROW\n");};columnCounter+=yyleng;updateArray("arrow");if(l == -1){return ARROW;};}
{less}{less}                   {if(l==1){printf("LSHIFT\n");};columnCounter+=yyleng;updateArray("lshift");if(l == -1){return LSHIFT;};}
{great}{great}                 {if(l==1){printf("RSHIFT\n");};columnCounter+=yyleng;updateArray("rshift");if(l == -1){return RSHIFT;};}
{xor}                          {if(l==1){printf("XOR\n");};columnCounter+=yyleng;updateArray("xor");if(l == -1){return XOR;};}
{bool}                         {if(l==1){printf("BOOL\n");};columnCounter+=yyleng;updateArray("bool");if(l == -1){return BOOL;};}
{class}                        {if(l==1){printf("CLASS\n");};columnCounter+=yyleng;updateArray("class");if(l == -1){return CLASS;};}
{dotlength}                    {if(l==1){printf("DOTLENGTH\n");};columnCounter+=yyleng;updateArray("dotlength");if(l == -1){return DOTLENGTH;};}
{double}                       {if(l==1){printf("DOUBLE\n");};columnCounter+=yyleng;updateArray("double");if(l == -1){return DOUBLE;};}
{else}                         {if(l==1){printf("ELSE\n");};columnCounter+=yyleng;updateArray("else");if(l == -1){return ELSE;};}
{if}                           {if(l==1){printf("IF\n");};columnCounter+=yyleng;updateArray("if");if(l == -1){return IF;};}
{int}                          {if(l==1){printf("INT\n");};columnCounter+=yyleng;updateArray("int");if(l == -1){return INT;};}
{print}                        {if(l==1){printf("PRINT\n");};columnCounter+=yyleng;updateArray("print");if(l == -1){return PRINT;};}
{parseint}                     {if(l==1){printf("PARSEINT\n");};columnCounter+=yyleng;updateArray("parseint");if(l == -1){yylval.col = columnCounter-yyleng;return PARSEINT;};}
{public}                       {if(l==1){printf("PUBLIC\n");};columnCounter+=yyleng;updateArray("public");if(l == -1){return PUBLIC;};}
{return}                       {if(l==1){printf("RETURN\n");};columnCounter+=yyleng;updateArray("reserved");if(l == -1){return RETURN;};}
{static}                       {if(l==1){printf("STATIC\n");};columnCounter+=yyleng;updateArray("static");if(l == -1){return STATIC;};}
{string}                       {if(l==1){printf("STRING\n");};columnCounter+=yyleng;updateArray("string");if(l == -1){return STRING;};}
{void}                         {if(l==1){printf("VOID\n");};columnCounter+=yyleng;updateArray("void");if(l == -1){return VOID;};}
{while}                        {if(l==1){printf("WHILE\n");};columnCounter+=yyleng;updateArray("while");if(l == -1){return WHILE;};}
{reserved}                     {if(l==1){printf("RESERVED(%s)\n",yytext);};columnCounter+=yyleng;updateArray("reserved");if(l == -1){makepacket(columnCounter,yytext); return RESERVED;};}
{id}                           {if(l==1){printf("ID(%s)\n", yytext);};columnCounter+=yyleng;updateArray("id");if(l == -1){makepacket(columnCounter,yytext);return ID;};}
" "|"\t"                       {columnCounter+=yyleng;}
\n|\r|\r\n                     {lineCounter++;columnCounter=1;lineOpCounter=0;memset(strlit,0,sizeof(strlit));}
{nullito}                      {columnCounter+=yyleng;}
<<EOF>>												 {yyterminate();}
.                              {if(e1 == 1){printf("Line %d, col %d: illegal character (%s)\n",lineCounter,columnCounter,yytext);};columnCounter+=yyleng;}

%%

int main(int argc, char* argv[]){
  for(int i=0;i<argc;i++){
  
      if(argv[1] == NULL){    
          l = -1;
          e1 = 1;
          e2 = 2;
          s1 = 1;
          semantics = 1;
      }else if(strcmp(argv[i],"-l")==0){
          l = 1;
          e1 = 1;
      }else if(strcmp(argv[i],"-e1")==0){
          e1 = 1;
      }else if(strcmp(argv[i],"-e2")==0){
          l = -1;
          e1 = 1;
      }else if(strcmp(argv[1], "-t")==0){
			    l = -1;
          e1 = 1;
          e2 = 2;
		  }else if(strcmp(argv[1], "-s")==0){
          l = -1;
          e1 = 1;
          e2 = 2;
          s1 = 1;
      }

  }
  if(l==0 && e1==0){
    e1 = 1;
  }
  if(l==-1){
    yyparse();
    if(fatalities == 0 && e1 == 1 && e2 == 2)
    {
      /*imprime tabela*/
      if(s1 == 1){
        printThemTables(root,semantics);
        if(semantics==0){
          printThemTrees(root,0);
        }
      }else{
        /*imprime arvore*/
        printThemTrees(root,0);
      }
      /*destroi arvore*/
      destroyThemTrees(root);
    }
  }else{
    yylex();
  }

  return 0;
}

int yywrap(){
  return 1;
}