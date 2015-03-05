# ==================================
#  LSD makefile
# ==================================

SHELL=/bin/bash

all: lsd

debug: flex
	gcc *.c -o compiler -g

lsd: flex gcc
	
flex: bison
	flex *.l
	
bison:
	bison -dty *.y
	
gcc:
	gcc *.c -o compiler

clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f y.tab.h
	rm -f y.tab.c

mrproper: clean
	rm -f compiler