#!/bin/sh

lex jucompiler.l
yacc -d jucompiler.y
cc -o jucompiler SyntaxTree.c SymTable.c y.tab.c lex.yy.c
./jucompiler -s < factorial.txt
