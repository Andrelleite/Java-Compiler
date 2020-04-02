#!/bin/sh

lex jucompiler.l
yacc -d jucompiler.y
cc -o jucompiler SyntaxTree.c y.tab.c lex.yy.c
./jucompiler -e2 < factorial.txt
