%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char * msg);
	int ligne;
	extern FILE * yyin;
%}
%union { char sval[0x100]; }
%token MOT PONCTUATION POINT
%type <sval> MOT phrase listePhrase phraseFin PONCTUATION POINT
%start phrase
%%
phrase : listePhrase POINT				{ printf("REDUCTION : phrase --> listePhrase (%s) POINT (%s)\n", $1, $2); sprintf($$, "%s %s", $1, $2); printf("[axiome phrase --> %s]\n", $$);}
;
listePhrase	: listePhrase PONCTUATION phraseFin	{ printf("REDUCTION : listePhrase --> listePhrase (%s) PONCTUATION (%s) phraseFin (%s)\n", $1, $2, $3); sprintf($$, "%s %s %s", $1, $2, $3); }
		| phraseFin				{ printf("REDUCTION : listePhrase --> phraseFin (%s)\n", $1); sprintf($$, "%s", $1); }
;
phraseFin	: phraseFin MOT				{ printf("REDUCTION : phraseFin --> phraseFin (%s) MOT (%s)\n", $1, $2); sprintf($$, "%s %s", $1, $2); }
		| MOT					{ printf("REDUCTION : phraseFin --> MOT (%s)\n", $1); sprintf($$, "%s", $1); }
;
%%
void yyerror(const char * msg) {
	fprintf(stderr, "%s.\n",msg);
}

int main(int argc, char ** argv) {
	if (argc>1) yyin = fopen(argv[1],"r");
	ligne = 1;
	if (!yyparse()) return printf("Analyse sémantique réussie sans encombres !!!\n");
	return(1);
}
