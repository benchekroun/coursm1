etat(node(E,H),E).
node_initial(N):- N is node(E), etat_intial(E).
node_final(N):- N is node(E), etat_final(E).
f(N,F):- N is node(E), heuristique(E,F).

algoRechEscalade(N,N):- node_final(N),!.

algoRechEscalade(N, Nsol):- 
findall((F,Nvoisin),(suivant(N,Nvoisin,f(Nvoisin,F)),NoeudsVoisins),	sort(NoeudsVoisins,[(NVMF,NoeudsVoisinsMin)|_]),
f(N,NF),
NVMF >= NF -> Nsol=N ; algoRechEscalade(NoeudsVoisinsMin,Nsol).

goEscalade(Solution):-
	noeud_initial(Ninit),
	algoRechEscalade(Ninit,Solution).
