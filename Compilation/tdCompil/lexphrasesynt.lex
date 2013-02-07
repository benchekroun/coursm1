%{
	#include <stdio.h>
	extern int ligne;
	void yyerror(const char * msg);
	int chr = 0;
	#include "phrasesynt.h"
%}
%option noyywrap
mot 		[a-z]+
ponctuation	,|;|\:
point		\?|\.|!
endOfLine	\n
%%
{mot}		{ chr += yyleng; return(MOT); }
{ponctuation}	{ chr += yyleng; return(PONCTUATION); }
{point}		{ chr += yyleng; return(POINT); }
{endOfLine}	{ ligne++; chr = 0; }
[[:blank:]]+	{ chr += yyleng; }
<<EOF>>		{ return printf("[Fichier complètement analysé]\n"); }
.		{ char msg[100]; sprintf(msg,"Erreur lexicale à la ligne %d au caractère %d (caractère %c du mot %s)\n", ligne, chr, yytext[0],yytext); yyerror(msg); return 1; }
%%
