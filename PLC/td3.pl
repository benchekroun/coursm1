
% 1-affiche tous les elements de la liste
affiche([]).
affiche([T|Q]):- write(T),affiche(Q).

% 2-affiche tous les elements de la liste en ordre inverse
affiche2([]).
affiche2([T|Q]):- affiche2(Q),write(T).

% 3-retrouve le premier element d'une liste
premier1([T|Q],T).

% 4-vrai si le premier element de L est affiche
premier2([T|Q]):- write(T).

% 5-retorune le dernier element de la liste
dernier1([T|[]],T).
dernier1([T|Q],X):- dernier1(Q,X).

% 6-affiche le dernier element de la liste
dernier2([T|[]]):- write(T).
dernier2([T|Q]):- dernier2(Q).

% 7-reconnaitre si X est element de L
element(T,[T|_]).
element(X,[T|Q]):- X \== T, element(X,Q).

% 8-compte le nombre d'elements de L
compte([],0).
compte([T|Q],N):-compte(Q,Y), N is Y+1.

% 9-fais la somme des elements de la liste
somme([T|[]],T).
somme([T|Q],N):- somme(Q,Y),N is Y+T. 

% 10-donne le Nieme element de la liste
nieme(1,[X|_],X).
nieme(N,[T|Q],X):- nieme(Y,Q,X),N is Y+1.

% 11-compte le nombre d'occurence d'un objet
occurence([],_,0).
occurence([X|Q],X,N):- occurence(Q,X,Z), N is Z+1.
occurence([T|Q],X,N):- X \== T, occurence(Q,X,N).
% mettre une coupure quelque part pour eviter les rappels de l'arbre



% enlever(X,L1,L2) L2 = L1\{X}.

enlever(X,[X|Q],Q).
enlever(X,[T|Q],[T|L]):-  enlever(X,Q,L).


% 12-Vrai si L& est sous ensemble de L2
ssens([],_).
ssens([T|Q],Lres):- element(T,Lres), enlever(T,Lres,L3), ssens(Q,L3).

