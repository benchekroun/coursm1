%nombre de cases mal placees
h1([],_,0).
%si la dernierer case est vide ("v")alors on renvoi 0 car bien placées
h1(["v"],_,0).
%case bien placée
h1([T|Q],T,N):- !,T2 is T+1, h1(Q,T2,N).
%case mal placées
h1([T|Q],A,N):- T2 is T+1, h1(Q,T2,N2),N is N2+1.
%en partant du principe que [1,2,3,4,5,6,7,8,o] est la solution
%ou [1,2,...,N,o] ets la solution de N

etat_final([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,"v"]).
