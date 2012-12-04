% :-include('monfichier.pl'). est une directive
etat9.

etat7([andre]):- etat9.

etat8([X|L]):- member(X,[bernard,babar,caroline]), etat9.

etat8([l|L]):- etat5(L).

etat8([la|L]):- etat10(L).

etat6([du|L]):- etat4(L).

etat6([d|L]):- etat7(L).

etat6([de|L]):- etat8(L).

etat4([X|L]):- member(X,[neveu,frere,pere]), etat6(L).

etat5([X|L]):- member(X,[oncle,ancetre]),etat6(L).

etat10([X|L]):- member(X,[mere,soeur]), etat6(L).

etat3([le|L]):- etat4(L).

etat3([l|L]):- etat5(L).

etat3([la|L]):- etat10(L).

etat1([qui|[est|L]]):- etat3(L).

analyse(L) :- etat1(L).

motVide(X):- member(X,[qui,est,le,la,l,de,du,d]);

nettoie([],L).

nettoie([T|Q],L):- \+motVide(X),append([X],L1,L),nettoie(Q,L1).  

