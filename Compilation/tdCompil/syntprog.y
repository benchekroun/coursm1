%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char * msg);
	int ligne;
	extern FILE * yyin;
%}
%token TYPE IDENTIFIANT PVIRG EGAL OPERATEUR POINT NOMBRE PARANTHESEOUV PARANTHESEFER FIN
%start prog
%%
prog : line;
line : affectation line | declaration line | affectation fin | declaration fin
;
declaration : TYPE IDENTIFIANT PVIRG;
affectation :  IDENTIFIANT EGAL expression PVIRG;
expression :  expression OPERATEUR expression | PARANTHESEOUV expression PARANTHESEFER | nombre;
nombre : NOMBRE | nbfloat;
nbfloat : NOMBRE POINT NOMBRE;
fin  : FIN;
%%
void yyerror(const char * msg) {
	fprintf(stderr, "%s.\n",msg);
}

int main(int argc, char ** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	ligne = 1;
	if (!yyparse()) return printf("Analyse syntaxique réussie sans encombres !!!\n");
	return 1;
}
