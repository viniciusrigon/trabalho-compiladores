#
# UFRGS - Compiladores B - Marcelo Johann - 2010/2 - Etapa 5
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#
# 
all: etapa5

etapa5: lex.yy.o main.o hash.o y.tab.o ast.o tacs.o semantic.o
	gcc lex.yy.o main.o y.tab.o hash.o ast.o semantic.o tacs.o -o etapa5
	
lex.yy.o: lex.yy.c y.tab.h
	gcc -c lex.yy.c
	
y.tab.o: y.tab.c
	gcc -c y.tab.c

main.o: main.c 
	gcc -c main.c
	
hash.o: hash.c
	gcc -c hash.c
	
ast.o: ast.c
	gcc -c ast.c

semantic.o: semantic.c
	gcc -c semantic.c

tacs.o: tacs.c
	gcc -c tacs.c

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l
	
y.tab.h: parser.y
	yacc -dv parser.y 

y.tab.c: parser.y
	yacc -dv parser.y
	
clean:
	rm *.o lex.yy.c y.tab.c lex.yy.h y.tab.h etapa5

