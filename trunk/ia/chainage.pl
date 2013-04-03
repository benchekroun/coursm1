#chainage avant
#on code les regles
#regle(Nom,Liste de FAits)

#on code les fait
#fait(X).

ch_av(But):- fait(But). #,!. pour s'arreter des qu'on a trouver le but, 
#mais si on veux saturer la base, alors on doit continuer meme si
#on a trouver
ch_av(But):-
	regle(Nom,Liste), 
	faitValide(Liste),
	\+fait(Nom), #peut etre "!," ici?
	asserta(fait(Nom).),
	ch_av(But).
	
ch_av(But):-
	regle(Nom,Liste),
	faitValide(Liste),
	fait(Nom).
	
faitValide([]).	
faitValide([T|Q]):- fait(T),faitValide(Q).

