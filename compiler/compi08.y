/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

%{
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "sym.h"
#include "pcode.h"
#include "checker.c"

extern int num_lines;
extern char* yytext;

// to avoid 'implicit definition'
int yylex(void);
int yyerror(char *str);

ASTTREE root;
%}

// définition du type des variables $x
%union{
        int ival;
        char *sval;
        ASTTREE tval;
}

%token BTRUE BFALSE ID NB
%token INT BOOL
%token IF THEN ELSE FI WHILE DO OD
%token WRITE READ PRINT
%token PROGRAM PROC
%token VAR BEG END
%token SKIP
%token COMMA COLON POINT CPOINT

%left AND OR NOT
%left EQUAL
%left GT ST GTEQUAL STEQUAL
%left MODULO
%left PLUS MINUS 
%left TIMES
%left LP RP
%left AFFECT

%type <tval> Program CodeBloc DeclVars DeclVar Code Instruction
%type <tval> ExprL ExprD EndIf Id Nb

%%

Program : PROGRAM Id CPOINT CodeBloc POINT { root = createNode(AT_ROOT, 0, NULL, $2, $4); }
;

CodeBloc : VAR DeclVars BEG Code END { $$ = createNode(AT_CODEB, 0, NULL, $2, $4);}
;

DeclVars :                  { $$ = NULL;}
         | DeclVar DeclVars { $$ = createNode(AT_DECLVARS, 0, NULL, $1, $2);}
;

DeclVar : Id COLON INT CPOINT  { $$ = createNode(AT_DECLINT, TYPE_INT, NULL, $1, NULL);}
        | Id COLON BOOL CPOINT { $$ = createNode(AT_DECLBOOL, TYPE_BOOL, NULL, $1, NULL);}
;

Code :                         { $$ = NULL; }
     | Instruction             { $$ = createNode(AT_LINSTR, 0, NULL, $1, NULL);}
     | Instruction CPOINT Code { $$ = createNode(AT_CODE, 0, NULL, $1, $3);}
;

Instruction : SKIP                  {$$ = NULL;}
            | ExprL AFFECT ExprD    {$$ = createNode(AT_AFFEXPR, 0, NULL, $1, $3);}
            | READ ExprD            {$$ = createNode(AT_OPREAD, 0, NULL, $2, NULL);}
            | WRITE ExprD           {$$ = createNode(AT_OPWRITE, 0, NULL, $2, NULL);}
            | IF ExprD THEN EndIf   {$$ = createNode(AT_OPIF, 0, NULL, $2, $4);}
            | WHILE ExprD DO Code OD {$$ = createNode(AT_OPWHILE, 0, NULL, $2, $4);}
;

EndIf : Code ELSE Code FI {$$ = createNode(AT_OPELSEFI, 0, NULL, $1, $3);}
;

ExprL : Id    {$$ = $1;}
;

//Expression Integer
ExprD : Nb                 {$$ = $1;}
      | ExprL              {$$ = $1;}
      | ExprD PLUS ExprD   {$$ = createNode(AT_OPADD, 0, NULL, $1, $3);} 
      | ExprD MINUS ExprD  {$$ = createNode(AT_OPSUB, 0, NULL, $1, $3);}
      | ExprD TIMES ExprD  {$$ = createNode(AT_OPMUL, 0, NULL, $1, $3);}
      | LP ExprD RP        {$$ = $2;}
      | ExprD MODULO ExprD {$$ = createNode(AT_OPMOD, 0, NULL, $1, $3);}
      | BFALSE              {$$ = createNode(AT_FALSE, 0, yylval.sval, NULL, NULL);}
      | BTRUE               {$$ = createNode(AT_TRUE, 1, yylval.sval, NULL, NULL);}
      | ExprD AND ExprD     {$$ = createNode(AT_OPBAND, 0, NULL, $1, $3);}
      | ExprD OR ExprD      {$$ = createNode(AT_OPBOR, 0, NULL, $1, $3);}
      | NOT ExprD           {$$ = createNode(AT_OPBNOT, 0, NULL, $2, NULL);}
      | ExprD EQUAL ExprD   {$$ = createNode(AT_OPBEQUAL, 0, NULL, $1, $3);}
      | ExprD GT ExprD      {$$ = createNode(AT_OPBGT, 0, NULL, $1, $3);}//GT= greater than '>'
      | ExprD ST ExprD      {$$ = createNode(AT_OPBST, 0, NULL, $1, $3);}//ST= smaller than '<'
      | ExprD STEQUAL ExprD {$$ = createNode(AT_OPBSTEQ, 0, NULL, $1, $3);}
      | ExprD GTEQUAL ExprD {$$ = createNode(AT_OPBGTEQ, 0, NULL, $1, $3);}
;

Id : ID { $$ = createNode(AT_ID, 0, yylval.sval, NULL, NULL);}
;

Nb : NB { $$ = createNode(AT_NB, yylval.ival, NULL, NULL, NULL);}
;

%%

int yyerror(char *str)
{
        fprintf(stderr,"KO\n");
        printf("ERROR '%s' AT LINE  %d : UNRECOGNISED '%s'\n",
                str,num_lines,yytext);
        exit(0);
}

int main()
{ 
  SYMTABLE sym;

  printf("; *** Compiler08_01\n");
  printf("; *** Gr08 Mertens Xavier Motte Josue, 2015\n");
  printf(";\n");

  printf(";*** BEGIN yyparse() ***\n");
  yyparse();
  printf(";*** END yyparse() ***\n");
  
  printf(";*** BEGIN printTree(..) ***\n");
  printTree(root);
  printf(";*** END printTree(..) ***\n");

  printf(";*** BEGIN SymbolTable ***\n");
  sym = createSymbolTable();
  fillSymbolTable(root, sym);
  printf(";*** END SymbolTable ***\n");
  
  printf(";*** BEGIN printSymbolTable(..) ***\n");
  printSymbolTable(sym);
  printf(";*** END printSymbolTable(..) ***\n");

  printf(";*** BEGIN computeLocations(..) ***\n");
  computeLocations(sym);
  printf(";*** END computeLocations(..) ***\n");

  printf(";*** BEGIN printSymbolTable(..) +locations ***\n");
  printSymbolTable(sym);
  printf(";*** END printSymbolTable(..) +locations ***\n");

  printf(";*** BEGIN validType(..) ***\n");
  //validType(root);
  printf(";*** END validType(..) ***\n");

  printf(";*** BEGIN PCodeGeneration ***\n");
  pcodeGenValue(root, sym);
  printf(";*** END PCodeGeneration ***\n");
  
  printf(";*** BEGIN Cleaning ***\n");
  freeNode(root);
  freeSymbolTable(sym);
  printf(";*** END Cleaning ***\n");

  fprintf(stderr,"OK\n");
  
  return 0;
}
