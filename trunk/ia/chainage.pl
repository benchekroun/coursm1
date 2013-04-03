#chainage avant
#on code les regles
#regle(Nom,Liste de FAits)

#on code les fait
#fait(X).

fait(pomme).
fait(farine).
fait(poire).
fait(oeuf).
fait(sel).
fait(abricot).
fait(beurre).

regle(pate,[farine,beurre,oeuf,sel]).
regle(pommeSucre,[pomme,sucre]).
regle(tartePomme,[pommeSucre,pate]).
regle(tarteAbricot,[pate,abricot]).
regle(tartePoire,[pate,poire]).
regle(tarteCerise,[pate,cerise]).

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


	
ch_av_sat():-
   regle(Nom,Liste),
   \+fait(Nom).
   faitValide(Liste),
   asserta(fait(Nom).),
   ch_av_sat.
   
ch_av_sat.

#saturation
ch_av(But):-
	ch_av_sat,
	fait(But).

#chainage arrière
ch_ar(But):-fait(But),!.
ch_ar(But):-
	regle(But,Liste),
	arValide(Liste).
	
arValide([]).
arValide([T|Q]):- ch_ar(T),arValide(Q).
