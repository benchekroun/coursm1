analyse(L) :-
	etat1(L).
etat1([qui,est|L]) :- 
	etat3(L).
etat3([le|L]) :- 
	etat4(L).
etat3([l|L]) :- 
	etat5(L).
etat3([la|L]) :- 
	etat10(L).
etat4([P|L]) :- 
	member(P,[parent,pere,fils,frere,grand_parent,grand_pere,petit_enfant,petit_fils,cousin]), etat6(L).
etat5([P|L]) :-  
	member(P,[ancetre,oncle,enfant]), etat6(L).
etat6([du|L]) :- 
	etat4(L).
etat6([d|L]) :- 
	etat7(L).
etat6([de|L]) :- 
	etat8(L).
etat7([P|L]) :- 
	homme(P), etat9(L).
etat7([P|L]) :- 
	femme(P), etat9(L).
etat8([P|L]) :- 
	homme(P), etat9(L).
etat8([P|L]) :- 
	femme(P), etat9(L).
etat8([l|L]) :- 
	etat5(L).
etat8([la|L]) :- 
	etat10(L).
etat10([P|L]) :- 
	element(P,[mere,fille,soeur,grand_mere,petite_fille,tante,cousine]), etat6(L).
etat9([]).

%% motVide répond vrai si le mot passé en paramètre fait partie des mot inutiles dans le traitement des questions

motvide(X) :- 
	member(X,[qui,est,le,la,l,du,de,d]).

%% Nettoie une question de ses mots vides.

nettoie([],[]).
nettoie([X|R],R1) :- 
	motvide(X),!,nettoie(R,R1).
nettoie([Y|R],[Y|R1]) :- 
	nettoie(R,R1).

/*
reponse1([Predicat,Individu],X) vrai si X est une réponse à la question
initiale qui avait été posée : on traite dans un premier temps uniquement les
questions sans emboîtement (du genre "qui est le père de babar ?") qui,
après nettoyage, donnent une liste à 2 éléments comme [pere,babar]
*/

reponse1([Predicat,Individu],X) :- 
	T =..[Predicat,X,Individu],
	call(T).

/*
Même que response1, mais avec les prédicats avec emboitement (du genre "qui est le
cousin du pere de dagobert ?"). Il peut y avoir un nombre non
borné d'emboitements
*/

reponse([P,Individu], X) :- 
	T =..[P,X,Individu],
	call(T).
reponse([P|L],X) :- 
	length([P|L],N),
	N>1,
	T=..[P,X,Y],
	call(T),
	reponse(L,Y).

/*
analyse(Q,R) : prédicat qui analyse une question Q complète (avec analyse
syntaxique et sémantique) et donne sa réponse dans R.
*/

analyse(Q,R) :- 
	analyse(Q),
	nettoie(Q,M),
	setof(X,reponse(M,X),R).

