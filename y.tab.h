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
    DOTLENGTH = 260,
    DOUBLE = 261,
    ELSE = 262,
    IF = 263,
    INT = 264,
    PRINT = 265,
    PUBLIC = 266,
    RETURN = 267,
    STATIC = 268,
    STRING = 269,
    VOID = 270,
    WHILE = 271,
    SEMICOLON = 272,
    BLANKID = 273,
    AND = 274,
    STAR = 275,
    ARROW = 276,
    COMMA = 277,
    DIV = 278,
    EQ = 279,
    GE = 280,
    GT = 281,
    LBRACE = 282,
    LE = 283,
    LPAR = 284,
    LSQ = 285,
    LT = 286,
    MINUS = 287,
    MOD = 288,
    NE = 289,
    NOT = 290,
    OR = 291,
    PLUS = 292,
    RBRACE = 293,
    RPAR = 294,
    RSQ = 295,
    XOR = 296,
    LSHIFT = 297,
    RSHIFT = 298,
    ID = 299,
    RESERVED = 300,
    INTLIT = 301,
    REALLIT = 302,
    STRLIT = 303,
    BOOLLIT = 304,
    UNARY = 305,
    ASSIGN = 306,
    PARSEINT = 307
  };
#endif
/* Tokens.  */
#define BOOL 258
#define CLASS 259
#define DOTLENGTH 260
#define DOUBLE 261
#define ELSE 262
#define IF 263
#define INT 264
#define PRINT 265
#define PUBLIC 266
#define RETURN 267
#define STATIC 268
#define STRING 269
#define VOID 270
#define WHILE 271
#define SEMICOLON 272
#define BLANKID 273
#define AND 274
#define STAR 275
#define ARROW 276
#define COMMA 277
#define DIV 278
#define EQ 279
#define GE 280
#define GT 281
#define LBRACE 282
#define LE 283
#define LPAR 284
#define LSQ 285
#define LT 286
#define MINUS 287
#define MOD 288
#define NE 289
#define NOT 290
#define OR 291
#define PLUS 292
#define RBRACE 293
#define RPAR 294
#define RSQ 295
#define XOR 296
#define LSHIFT 297
#define RSHIFT 298
#define ID 299
#define RESERVED 300
#define INTLIT 301
#define REALLIT 302
#define STRLIT 303
#define BOOLLIT 304
#define UNARY 305
#define ASSIGN 306
#define PARSEINT 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "jucompiler.y" /* yacc.c:1909  */

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
