%{
	#include <stdio.h>
	int ligne = 1;
	int chr = 1;
%}
%option noyywrap
mot 		[a-z]+
ponctuation	,|;|\:
point		\?|\.|!
endOfLine	\n
%%
{mot}		{ printf("Lexème reconnu pour le token MOT : ");		ECHO;	printf("\n");	chr += yyleng; }
{ponctuation}	{ printf("Lexème reconnu pour le token PONCTUATION : ");	ECHO;	printf("\n");	chr += yyleng; }
{point}		{ printf("Lexème reconnu pour le token POINT : ");		ECHO;	printf("\n");	chr += yyleng; }
{endOfLine}	{ ligne++; chr = 1; }
[[:blank:]]+	{ chr += yyleng; }
<<EOF>>		{ return printf("[Fichier complètement analysé]\n"); }
.		{ fprintf(stderr,"Erreur lexicale à la ligne %d au caractère %d (caractère %c du mot %s)\n", ligne, chr, yytext[0], yytext); return 1; }
%%
int main(int argc, char ** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	if (!yylex()) return printf("Analyse lexicale réussie sans encombres !!!\n");
	else return(1);
}

