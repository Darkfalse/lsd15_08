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
%token INT BOOL VOID
%token IF THEN ELSE FI WHILE DO OD
%token WRITE READ PRINT
%token PROGRAM PROC
%token VAR BEG END
%token SKIP
%token COMMA COLON POINT CPOINT

%left AND OR NOT
%left EQUAL
%left GT ST
%left MODULO
%left PLUS MINUS 
%left TIMES
%left LP RP
%left AFFECT

%type <tval> Program CodeBloc DeclVars DeclVar Code Instruction FinInstr
%type <tval> Expr ExprI ExprB EndIf Id Nb

%%

Program : PROGRAM Id CPOINT CodeBloc POINT { root = createNode(AT_ROOT, 0, NULL, $2, $4); }
;

CodeBloc : VAR DeclVars BEG Code END { $$ = createNode(AT_CODEB, 0, NULL, $2, $4);}
;

DeclVars :                  { $$ = NULL;}
         | DeclVars DeclVar { $$ = createNode(AT_DECLVARS, 0, NULL, $1, $2);}
;

DeclVar : Id COLON VOID CPOINT { $$ = createNode(AT_DECLVOID, 0, NULL, $1, NULL);}
        | Id COLON INT CPOINT  { $$ = createNode(AT_DECLINT, 0, NULL, $1, NULL);}
        | Id COLON BOOL CPOINT { $$ = createNode(AT_DECLBOOL, 0, NULL, $1, NULL);}
;

Code :                  { $$ = NULL; }
     | Code Instruction { $$ = createNode(AT_CODE, 0, NULL, $1, $2);}
;

Instruction : SKIP FinInstr         {$$ = NULL;}
            | Id AFFECT Expr FinInstr {$$ = createNode(AT_AFFEXPR, 0, NULL, $1, $4);}
            | Id AFFECT Id FinInstr   {$$ = createNode(AT_AFFID, 0, NULL, $1, $4);}
            | READ ExprI FinInstr   {$$ = createNode(AT_OPREAD, 0, NULL, $2, NULL);}
            | WRITE ExprI FinInstr  {$$ = createNode(AT_OPWRITE, 0, NULL, $2, NULL);}
            | IF ExprB THEN EndIf   {$$ = createNode(AT_OPIF, 0, NULL, $2, $4);}
            | WHILE Expr DO Code OD {$$ = createNode(AT_OPWHILE, 0, NULL, $2, $4);}
;

EndIf : Code FI           {$$ = createNode(AT_OPFI, 0, NULL, $1, NULL);}
      | Code ELSE Code FI {$$ = createNode(AT_OPELSEFI, 0, NULL, $1, $3);}
;

FinInstr :        { $$ = NULL;}
         | CPOINT { $$ = NULL;}
;

Expr : ExprI {$$ = $1;}
     //Var   {$$ = $1;}
     | ExprB {$$ = $1;}
;

ExprI : Nb                 {$$ = $1;}
      | ExprI PLUS ExprI   {$$ = createNode(AT_OPADD, 0, NULL, $1, $3);} 
      | ExprI MINUS ExprI  {$$ = createNode(AT_OPSUB, 0, NULL, $1, $3);}
      | ExprI TIMES ExprI  {$$ = createNode(AT_OPMUL, 0, NULL, $1, $3);}
      | LP ExprI RP        {$$ = $2;}
      | ExprI MODULO ExprI {$$ = createNode(AT_OPMOD, 0, NULL, $1, $3);}
;

ExprB : BFALSE               {$$ = createNode(AT_FALSE, 0, yylval.sval, NULL, NULL);}
      | BTRUE                {$$ = createNode(AT_TRUE, 0, yylval.sval, NULL, NULL);}
      | ExprB AND ExprB      {$$ = createNode(AT_OPBAND, 0, NULL, $1, $3);}
      | ExprB OR ExprB       {$$ = createNode(AT_OPBOR, 0, NULL, $1, $3);}
      | NOT ExprB            {$$ = createNode(AT_OPBNOT, 0, NULL, $2, NULL);}
      | ExprB EQUAL ExprB    {$$ = createNode(AT_OPBEQUAL, 0, NULL, $1, $3);}
      | LP ExprB RP          {$$ = $2;}
      | ExprB GT ExprB       {$$ = createNode(AT_OPBGT, 0, NULL, $1, $3);}//GT= greater than '>'
      | ExprB ST ExprB       {$$ = createNode(AT_OPBST, 0, NULL, $1, $3);}//ST= smaller than '<'
      | ExprB ST EQUAL ExprB {$$ = createNode(AT_OPBSTEQ, 0, NULL, $1, $4);}
      | ExprB GT EQUAL ExprB {$$ = createNode(AT_OPBGTEQ, 0, NULL, $1, $4);}
;

Id : ID { $$ = createNode(AT_ID, 0, yylval.sval, NULL, NULL);}
;

Nb : NB { $$ = createNode(AT_NB, yylval.ival, NULL, NULL, NULL);}
;

//Var : VAR { $$ = createNode(AT_VAR, 0, yylval.sval, NULL, NULL);}
//;

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
  printf("; *** Gr08 Mertens Xavier Motte Josué, 2015\n");
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
