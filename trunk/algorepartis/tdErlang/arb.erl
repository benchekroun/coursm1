-module(arb).
-export([couleur/1,fg/1,fd/1,valeur/1,noeud/4,build/0]).


couleur(feuille) -> noir;
couleur({C,_,_,_}) -> C.

fg({_,_,G,_}) -> G.
fd({_,_,_,D}) -> D.

valeur({_,V,_,_}) -> V.

noeud(C,V,G,D) -> {C,V,G,D}.

build() -> noeud(rouge,8,noeud(noir,1,feuille,noeud(rouge,6,feuille,feuille)),noeud(noir,11,feuille,feuille)).
