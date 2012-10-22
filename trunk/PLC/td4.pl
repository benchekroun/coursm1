% char_code('c',C) predicat qui permet de recuperer le code acii d'un char.

%concat d'une liste + un terme


plus3(X,Y,Z):- Z is X+Y.
mult3(X,Y,Z):- Z is X*Y.

appliquer(Op,[],[]).
appliquer(Op,[X],[X]).
appliquer(Op, [T|[T2|Q]],[Restmp|Rsuiv]):-
	Y =.. [Op,T,T2,Restmp], call(Y),
	appliquer(Op,Q,Rsuiv).

% version avec les operateurs standards
appliquer2(Op,[],[]).
appliquer2(Op,[X],[X]).
appliquer2(Op, [T|[T2|Q]],[Restmp|Rsuiv]):-
	Y =.. [Op,T,T2],
	Restmp is Y,
	appliquer2(Op,Q,Rsuiv).


p(1,3,5).
p(2,4,1).
p(3,5,2).
p(4,3,1).
p(5,2,4).

% bagof(Z,(X,Y)^p(X,Y,Z),Sac) met dans une liste toutes les valeur de Z , mais retire X et Y).

% si le but echoue, bagof echoue , alros que findall renvoi une liste vide.

myfindall

% rajouter un but avec assert