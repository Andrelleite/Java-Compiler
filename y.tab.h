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
    PARSEINT = 266,
    PUBLIC = 267,
    RETURN = 268,
    STATIC = 269,
    STRING = 270,
    VOID = 271,
    WHILE = 272,
    SEMICOLON = 273,
    BLANKID = 274,
    AND = 275,
    STAR = 276,
    ARROW = 277,
    COMMA = 278,
    DIV = 279,
    EQ = 280,
    GE = 281,
    GT = 282,
    LBRACE = 283,
    LE = 284,
    LPAR = 285,
    LSQ = 286,
    LT = 287,
    MINUS = 288,
    MOD = 289,
    NE = 290,
    NOT = 291,
    OR = 292,
    PLUS = 293,
    RBRACE = 294,
    RPAR = 295,
    RSQ = 296,
    XOR = 297,
    LSHIFT = 298,
    RSHIFT = 299,
    ID = 300,
    RESERVED = 301,
    INTLIT = 302,
    REALLIT = 303,
    STRLIT = 304,
    BOOLLIT = 305,
    UNARY = 306,
    ASSIGN = 307
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
#define PARSEINT 266
#define PUBLIC 267
#define RETURN 268
#define STATIC 269
#define STRING 270
#define VOID 271
#define WHILE 272
#define SEMICOLON 273
#define BLANKID 274
#define AND 275
#define STAR 276
#define ARROW 277
#define COMMA 278
#define DIV 279
#define EQ 280
#define GE 281
#define GT 282
#define LBRACE 283
#define LE 284
#define LPAR 285
#define LSQ 286
#define LT 287
#define MINUS 288
#define MOD 289
#define NE 290
#define NOT 291
#define OR 292
#define PLUS 293
#define RBRACE 294
#define RPAR 295
#define RSQ 296
#define XOR 297
#define LSHIFT 298
#define RSHIFT 299
#define ID 300
#define RESERVED 301
#define INTLIT 302
#define REALLIT 303
#define STRLIT 304
#define BOOLLIT 305
#define UNARY 306
#define ASSIGN 307

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
