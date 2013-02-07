%{
	#include <stdio.h>
	int ligne = 1;
	int chr = 1;
%}
%option noyywrap
type		"int"[[:blank:]]+|float[[:blank:]]+
identifiant 	[a-zA-Z]+
pvirg		;
egal 		=
operateur  	\+|-|\*|\/
point 		\.
nombre		[0-9]+
parantheseOuv 	\(
parantheseFer	\)
endOfLine	\n
%%
{type}		{printf("Lexème reconnu pour le token TYPE : ");		ECHO;	printf("\n");}
{identifiant}	{printf("Lexème reconnu pour le token IDENTIFIANT : ");		ECHO;	printf("\n");}
{pvirg}		{printf("Lexème reconnu pour le token POINTVIRGULE : ");	ECHO;	printf("\n");}
{egal}		{printf("Lexème reconnu pour le token EGAL : ");		ECHO;	printf("\n");}
{operateur}	{printf("Lexème reconnu pour le token OPERATEUR : ");		ECHO;	printf("\n");}
{point}		{printf("Lexème reconnu pour le token POINT : ");		ECHO;	printf("\n");}
{nombre}	{printf("Lexème reconnu pour le token NOMBRE : ");		ECHO;	printf("\n");}
{parantheseOuv}	{printf("Lexème reconnu pour le token PARANTHESEOUV : ");	ECHO;	printf("\n");}
{parantheseFer} {printf("Lexème reconnu pour le token PARANTHESEFER : ");	ECHO;	printf("\n");}
[[:blank:]]+
<<EOF>>		{ return printf("[Fichier complètement analysé]\n"); }
%%
int main(int argc, char ** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	if (!yylex()) return printf("Analyse lexicale réussie sans encombres !!!\n");
	else return(1);
}
