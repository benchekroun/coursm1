/*afficher N fois bonjour*/
ecrit(0).

ecrit(N):- N =\= 0, X is N-1,write('bonjour'),ecrit(X).

afficheOrdre(1):- write(1).
afficheOrdre(N):- N=\=1,X is N-1,afficheOrdre(X),write(N).