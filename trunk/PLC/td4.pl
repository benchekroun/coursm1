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

% si le but echoue, bagof echoue , alors que findall renvoi une liste vide.
% rajouter un but avec assert
:- dynamic(ok_pour/1).
myfindall(X,BUT,Sac):-
	resoudre(X,BUT),
	rassembler([],Sac).
	call(BUT), /* X instancé */
	assertz(ok_pour(X)),
	fail.
myfindall(_,_,_).
myfindall(X,_,[X|L]):- ok_pour(X), retract(ok_pour(X)).

p(X,Y) :- q(X),r(X,Y).
p(d,d1).

q(a).
q(b).
q(c).

r(b,b1).
r(c,c1).
r(a,a1).
r(a,a2).
r(a,a3).

/*
Donnez les solutions du but p(X,Y).
*/



p1(X,Y) :- q(X),r(X,Y),!. /* meme question que sur le but p(X,Y). */
p2(X,Y) :- q(X), ! ,r(X,Y). /* meme question que sur le but p(X,Y). */
p3(X,Y) :- ! , q(X),r(X,Y). /* meme question que sur le but p(X,Y). */
p3(d,d1).