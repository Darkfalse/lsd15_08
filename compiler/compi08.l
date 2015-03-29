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
%x comment

id        [A-Za-z][A-Za-z0-9]*
nbr       (0|[1-9][0-9]*)
blank     [ \t]+
comment   {[\n.]*}

%%
"{"          {BEGIN(comment);}
<comment>"}" {BEGIN(INITIAL);}
<comment>.   {}

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
"true"       {return BTRUE;}
"false"      {return BFALSE;}
"if"         {return IF;}
"then"       {return THEN;}
"else"       {return ELSE;}
"fi"         {return FI;}
"while"      {return WHILE;}
"do"         {return DO;}
"od"         {return OD;}
"write"      {return WRITE;}
"read"       {return READ;}


":="         {return AFFECT;}
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
"<="         {return STEQUAL;}
">="         {return GTEQUAL;}
">"          {return GT;}
"<"          {return ST;}

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

.            {
                fprintf(stderr,"KO\n");
                printf("ERROR : invalid '%s' in line %d\n",yytext, num_lines);
                exit(0);
             }

%%
