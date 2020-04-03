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
    ASSIGN = 276,
    STAR = 277,
    ARROW = 278,
    COMMA = 279,
    DIV = 280,
    EQ = 281,
    GE = 282,
    GT = 283,
    LBRACE = 284,
    LE = 285,
    LPAR = 286,
    LSQ = 287,
    LT = 288,
    MINUS = 289,
    MOD = 290,
    NE = 291,
    NOT = 292,
    OR = 293,
    PLUS = 294,
    RBRACE = 295,
    RPAR = 296,
    RSQ = 297,
    XOR = 298,
    LSHIFT = 299,
    RSHIFT = 300,
    RESERVED = 301,
    INTLIT = 302,
    REALLIT = 303,
    STRLIT = 304,
    BOOLLIT = 305,
    ID = 306,
    UNARY = 307
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
#define ASSIGN 276
#define STAR 277
#define ARROW 278
#define COMMA 279
#define DIV 280
#define EQ 281
#define GE 282
#define GT 283
#define LBRACE 284
#define LE 285
#define LPAR 286
#define LSQ 287
#define LT 288
#define MINUS 289
#define MOD 290
#define NE 291
#define NOT 292
#define OR 293
#define PLUS 294
#define RBRACE 295
#define RPAR 296
#define RSQ 297
#define XOR 298
#define LSHIFT 299
#define RSHIFT 300
#define RESERVED 301
#define INTLIT 302
#define REALLIT 303
#define STRLIT 304
#define BOOLLIT 305
#define ID 306
#define UNARY 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 40 "jucompiler.y" /* yacc.c:1909  */

    char* id;
    struct node* newNode;

#line 163 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
