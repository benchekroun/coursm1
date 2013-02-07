%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char * msg);
	int ligne;
	extern FILE * yyin;
%}
%token MOT PONCTUATION POINT
%start phrase
%%
phrase : listePhrase POINT				{fprintf(stderr,"phrase --> listePhrase POINT (%d)\n", POINT);}
;
listePhrase	: listePhrase PONCTUATION phraseFin	{fprintf(stderr,"listePhrase --> listePhrase PONCTUATION (%d) phraseFin\n", PONCTUATION);}
		| phraseFin				{fprintf(stderr,"listePhrase --> phraseFin\n");}
;
phraseFin	: phraseFin MOT				{fprintf(stderr,"phraseFin --> phraseFin MOT (%d)\n", MOT);}
		| MOT					{fprintf(stderr,"phraseFin --> MOT (%d)\n", MOT);}
;
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
