%exercice 2 

%donner un description des états , du voisinage et la taille du voisinage
% toutes les reines doivent etre sur l'échiquier et une par case, et une seule par colonne,(sinon on ne peut pas restreindre les déplacement a la ligne), le voisinage est de bouger une reine dans sa colonne( N*N-1 voisins , car on a n reines qui peuvent se déplacer dans n-1 cases) la fonctino à optimiser c'est le nombre de conflict

% comme chaque reine est sur une colonne on a juste besoin de leur coordonnée de ligne

generer(0,[]).
generer(N,[1|L2]):- generer(N-1,L2).

node_init(L):- taille(N),generer(N,L).
node_final(L):-
	f(L,0).

f(L,N):-
	f_ligne(L,Nl,[]),
	f_diag(L,1,Nd),
	N is Nl+Nd.

%ligne
f_ligne([],0,_).
f_ligne([T|Q],NL,DejaVu):- member(T,DejaVu),!,f_ligne(Q,N2,DejaVu),NL is N2+1.
f_ligne([T|Q],NL,DejaVu):- f_ligne(Q,NL,[T|DejaVu]).

%diag
f_diag([T],_,0).

algoRechEscalade(N,N):- node_final(N),!.

algoRechEscalade(N, Nsol):- 
findall((F,Nvoisin),(suivant(N,Nvoisin,f(Nvoisin,F)),NoeudsVoisins),	sort(NoeudsVoisins,[(NVMF,NoeudsVoisinsMin)|_]),
f(N,NF),
NVMF >= NF -> Nsol=N ; algoRechEscalade(NoeudsVoisinsMin,Nsol).

goEscalade(Solution):-
	noeud_initial(Ninit),
	algoRechEscalade(Ninit,Solution).
