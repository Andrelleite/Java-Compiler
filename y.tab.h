/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    CLASS = 259,
    DOUBLE = 260,
    INT = 261,
    PUBLIC = 262,
    STATIC = 263,
    STRING = 264,
    VOID = 265,
    SEMICOLON = 266,
    BLANKID = 267,
    COMMA = 268,
    LBRACE = 269,
    LPAR = 270,
    LSQ = 271,
    RBRACE = 272,
    RPAR = 273,
    RSQ = 274,
    LSHIFT = 275,
    RSHIFT = 276,
    ID = 277,
    RESERVED = 278,
    INTLIT = 279,
    REALLIT = 280,
    STRLIT = 281,
    BOOLLIT = 282,
    UNARY = 283,
    ASSIGN = 284,
    PARSEINT = 285,
    LE = 286,
    EQ = 287,
    LT = 288,
    GE = 289,
    GT = 290,
    NE = 291,
    OR = 292,
    AND = 293,
    MINUS = 294,
    MOD = 295,
    DIV = 296,
    STAR = 297,
    PLUS = 298,
    XOR = 299,
    PRINT = 300,
    RETURN = 301,
    DOTLENGTH = 302,
    ARROW = 303,
    WHILE = 304,
    NOT = 305,
    IF = 306,
    ELSE = 307
  };
#endif
/* Tokens.  */
#define BOOL 258
#define CLASS 259
#define DOUBLE 260
#define INT 261
#define PUBLIC 262
#define STATIC 263
#define STRING 264
#define VOID 265
#define SEMICOLON 266
#define BLANKID 267
#define COMMA 268
#define LBRACE 269
#define LPAR 270
#define LSQ 271
#define RBRACE 272
#define RPAR 273
#define RSQ 274
#define LSHIFT 275
#define RSHIFT 276
#define ID 277
#define RESERVED 278
#define INTLIT 279
#define REALLIT 280
#define STRLIT 281
#define BOOLLIT 282
#define UNARY 283
#define ASSIGN 284
#define PARSEINT 285
#define LE 286
#define EQ 287
#define LT 288
#define GE 289
#define GT 290
#define NE 291
#define OR 292
#define AND 293
#define MINUS 294
#define MOD 295
#define DIV 296
#define STAR 297
#define PLUS 298
#define XOR 299
#define PRINT 300
#define RETURN 301
#define DOTLENGTH 302
#define ARROW 303
#define WHILE 304
#define NOT 305
#define IF 306
#define ELSE 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 43 "jucompiler.y" /* yacc.c:1909  */

    int col;
    struct uni* loki;
    struct node* newNode;

#line 164 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
