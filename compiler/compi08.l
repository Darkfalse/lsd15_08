/* Groupe 8
 * Mertens Xavier
 * Motte Josué
 * 2015
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "y.tab.h"

int num_lines=1;
%}

%option noyywrap

id        [A-Za-z][A-Za-z0-9]*
nbr       (0|-?[1-9][0-9]*)
blank     [ \t]+
comment   "{"[.*]"}"

%%
"program"    {return PROGRAM;}
"var"        {return VAR;}
"begin"      {return BEG;}
"end"        {return END;}
"skip"       {return SKIP;}
"procedure"  {return PROC;}

"and"        {return AND;}
"or"         {return OR;}
"not"        {return NOT;}
"integer"    {return INT;}
"boolean"    {return BOOL;}
"void"       {return VOID;}
"true"       {return BTRUE;}
"false"      {return BFALSE;}
"if"         {return IF;}
"then"       {return THEN;}
"else"       {return ELSE;}
"fi"         {return FI;}
"while"      {return WHILE;}
"do"         {return DO;}
"od"         {return OD;}
"print"      {return PRINT;}
"read"       {return READ;}

"="          {return EQUAL;}
"+"          {return PLUS;}
"-"          {return MINUS;}
"*"          {return TIMES;}
"("          {return LP;}
")"          {return RP;}
","          {return COMMA;}
"."          {return POINT;}
":"          {return COLON;}
";"          {return CPOINT;}
">"          {return GT;}
"<"          {return ST;}
"mod"        {return MODULO;}
":="         {return AFFECT;}

{id}         {
                yylval.sval=(char*)calloc(strlen(yytext)+1,sizeof(char));
		strcpy(yylval.sval,yytext);
		return ID;
             }

{nbr}        {
                yylval.ival=atoi(yytext);
		return NB;
             }

"\n"         {++num_lines;}

{blank}      {/*On passe*/}

{comment}    {/*On passe aussi*/}

.            {
                fprintf(stderr,"KO\n");
                printf("ERROR : invalid '%s' in line %d\n",yytext, num_lines);
                exit(0);
             }

%%
