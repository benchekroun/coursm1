%{
	#include <stdio.h>
	extern int ligne;
	void yyerror(const char * msg);
	int chr = 0;
	#include "phrasesem.h"
%}
%option noyywrap
mot 		[a-z]+
ponctuation	,|;|\:
point		\?|\.|!
endOfLine	\n
%%
{mot}		{ sprintf(yylval.sval, "%s", yytext);	chr += yyleng; return(MOT); }
{ponctuation}	{ sprintf(yylval.sval, "%s", yytext);	chr += yyleng; return(PONCTUATION); }
{point}		{ sprintf(yylval.sval, "%s", yytext);	chr += yyleng; return(POINT); }
{endOfLine}	{ ligne++; chr = 0; }
[[:blank:]]+	{ chr += yyleng; }
<<EOF>>		{ printf("[Fichier lexicalement analysé]\n"); return 0; }
.		{ char msg[100]; sprintf(msg,"Erreur lexicale à la ligne %d au caractère %d (caractère %c du mot %s)\n", ligne, chr, yytext[0],yytext); yyerror(msg); return 1; }
%%
