%il faut penser a préciser certain prédicat pour faire fonctionner le moteur

%noeud_init(-N). "-" pour dire que le N ets en sortie
%noeud_final(+N). repond true si N est final
%action(+E1, -E2, -Action). prend l'état 1 , calcul l'état 2 et donne l'action pour y arriver
%valide(+E). true si l'état est valide

%profondeur
goRp():-
noeud_init(N),
rp(N,[],Chemin). % on pensera a faire un reverse sur chemin genre reverse(chemin,Sol) pour ensuite afficher sol

rp(N,Djv,[N|Djv]):-
	noeud_final(N),!.

rp(node(E,Ac), Djv, Chemin):-
	action(E,Es,A),
	valide(Es),
	\+member(node(Es,_),[node(E,Ac)|Djv]),
	rp(Es,[node(E,Ac)|Djv],Chemin). %on se rappelle avec l'état suivant, et la magie prolog mettra tous les fils possibles dans Es 


%largeur
%petite subtilité, dnas la profondeur , on ne retient qu'une brache , c'est pourquoi , le Djv est séparé
%Ici, chacun des nodes de la liste à un chemin différent, donc
% on a une liste de liste de node avec l'eur chemin jusqu'a la racine 
%soit [[NoeudCourant|CheminPourRemonterALaRacine]|NoeudsAVisitePlusTard]

goRl():-
noeud_init(N),
rl([N],Chemin).

rl([[N|CheminPreced]|AutresNodes],[N|CheminPreced]):-
	noeud_final(N). 
%cas nominal
rl([[node(E,A)|ChemRoot]|Reste],Chemin):-
	findall(
	[node(Es,As)|[node(E,A)|ChemRoot]],%comment creer un des voisins
	(action(E,Es,As),valide(Es),\+member(node(Es,_), [ChemRoot|Reste])),%les conditions a vérifier pour que le suivant soit valide
	Fils),%fin du findall
	%nouvelle liste
	append(Reste,Fils,NewListe),
	%appel recursif
	rl(NewListe,Chemin).

%partie A*

%comme d'hab on a besoin de certain prédicat
%node(E,A,G,H) avec G , cout reel (cout node + cout chemin pour arriver), H: cout heuristique

%---prédicat a redefinir suivant le probleme
%Node_intial(?N). donne le noeud intial
%node_final(+N). true si le node est final
%h une fonction heuristique, qui donne donc la distance d'un état à l'état final

%on a besoin de redéfinir l'action
%action(+Ec, -Es, -A, -Cout)
%on oublie de remplacer NomAction par ce qu'on veux
action(E,Es,NomAction, Cout):-
	suivant(E,Es), %predicat adapté au problème, qui calcule un fils d'un noeud (le findall d'au dessus permtra d'avoir tous les fils)
	valide(Es),
	h(Es,Cout).

%getters
etat(node(E,_,_,_), E).
action(node(_,A,_,_), A).
coutReel(node(_,_,G,_), G).
coutEstime(node(_,_,_,H), H).

%intialisation et fin
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
