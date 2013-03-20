
etat_initial([1, 1, 1, 0, 1, 0]).
etat_final([0, 0, 0, 0, 0, 0]).


h1([], 0).
h1([T|Q], H) :- h1(Q, N), H is N+T.
h(E, H) :- h1(E, N), H is N / 2.


% Pour retourner une flèche
flip(0, 1).
flip(1, 0).

tourner([N|Q], 0, [M|Q]) :- flip(N, M).
tourner([N|Q1], 1, [M|Q2]) :- flip(N, M), tourner(Q1, 0, Q2).
tourner([T|Q1], N, [T|Q2]) :-
	N > 1, N1 is N - 1,
	tourner(Q1, N1, Q2).


action(Ec, Es, A, 1) :-
	member(Pos, [1,2,3,4,5]),
	A = turn(Pos),
	tourner(Ec, Pos, Es).


etat(node(E,_,_,_), E).
action(node(_,A,_,_), A).
coutReel(node(_,_,G,_), G).
coutEstime(node(_,_,_,H), H).


noeud_initial(node(E, debut, 0, H)) :- etat_initial(E), h(E, H).
noeud_final(node(E,_,_,_)) :- etat_final(E).

goAstar :- noeud_initial(N),
	rAstar([[N]], [], Sol, stat(1, 0), stat(NC, NE)),
	reverse(Sol, Chemin),
	write(Chemin), nl, write('Nb Noeuds créés: '), write(NC), nl, write('Nb Noeuds Explorés: '), write(NE), nl,
	Sol = [Last|_],
	coutReel(Last, C), write(C), !.

rAstar([[N|Chemin]|_], _, [N|Chemin], stat(NC, NE), stat(NC, NEN)) :-
	noeud_final(N), NEN is NE + 1.

rAstar([[N|Chemin]|Liste], DejaVu, Sol, stat(NC, NE), stat(NCS, NES)) :-
	findall([NS,N|Chemin], (noeud_suivant(N,NS), \+(dejaVu(NS, DejaVu))), L),
	inserer_tous(L, Liste, NewListe),
	length(L, NCP), NCN is NC + NCP, NEN is NE + 1,
	rAstar(NewListe, [N|DejaVu], Sol, stat(NCN, NEN), stat(NCS, NES)).

noeud_suivant(node(E,_,G,_), node(Es, As, Gs, Hs)) :-
	action(E, Es, As, C), Gs is G + C, h(Es, Hs).

dejaVu(node(E, _, G, H), [node(E, _, G1, H1)|_]) :-
	F is G + H, F1 is G1 + H1, F1 =< F, !.
dejaVu(N, [_|Q]) :- dejaVu(N, Q).

inserer_tous([], L2, L2).
inserer_tous(L1, [], L1).
inserer_tous([[T1|S1]|Q1], [[T2|S2]|Q2], [[T2|S2]|Q3]) :-
	coutReel(T1, G1), coutReel(T2, G2), coutEstime(T1, H1), coutEstime(T2, H2),
	F1 is G1 + H1, F2 is G2 + H2,
	F1 > F2, inserer_tous([[T1|S1]|Q1], Q2, Q3).
inserer_tous([[T1|S1]|Q1], [[T2|S2]|Q2], [[T1|S1]|Q3]) :-
	coutReel(T1, G1), coutReel(T2, G2), coutEstime(T1, H1), coutEstime(T2, H2),
	F1 is G1 + H1, F2 is G2 + H2,
	F1 =< F2, inserer_tous(Q1, [[T2|S2]|Q2], Q3).
%inserer_tous([T|Q1], L2, [T|Q2]) :- inserer_tous(Q1, L2, Q2).




