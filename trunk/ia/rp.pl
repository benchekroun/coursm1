%il faut penser a préciser certain prédicat pour faire fonctionner le moteur

%noeud_init
%noeud_final

goRp():-
noeud_init(N),
rp(n,[],Chemin). % on pensera a faire un reverse sur chemin genre reverse(chemin,Sol) pour ensuite afficher sol

rp(N,Djv,[N|Djv]):-
	noeud_final(N).

rp()
