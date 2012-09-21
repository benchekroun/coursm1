%les_hommes
homme(andre).
homme(bernard).
homme(clement).
homme(dudulle).
homme(damien).
homme(baptiste).
homme(cedric).
homme(didier).
homme(dagobert).
homme(dominique).
homme(babar).

%les_femmes
femme(augustine).
femme(becassine).
femme(chantal).
femme(daniela).
femme(celestine).
femme(brigitte).
femme(charlotte).
femme(caroline).

%parents

parent(andre,bernard).
parent(andre,brigitte).
parent(andre,babar).

parent(augustine,bernard).
parent(augustine,brigitte).
parent(augustine,babar).

parent(bernard,clement).
parent(bernard,celestine).

parent(becassine,clement).
parent(becassine,celestine).

parent(brigitte,cedric).
parent(brigitte,caroline).

parent(baptiste,cedric).
parent(baptiste,caroline).

parent(clement,dudulle).
parent(clement,damien).
parent(clement,daniela).

parent(chantal,dudulle).
parent(chantal,damien).
parent(chantal,daniela).

parent(cedric,didier).
parent(cedric,dagobert).
parent(cedric,dominique).

parent(charlotte,didier).
parent(charlotte,dagobert).
parent(charlotte,dominique).

%liens_parente
mere(X,Y):- parent(X,Y),femme(X).
pere(X,Y):- parent(X,Y),homme(X).
fils(X,Y):- parent(Y,X),homme(X).
fille(X,Y):- parent(Y,X),femme(X).
grand_parent(X,Z):- parent(X,Y),parent(Y,Z).
petit_enfant(X,Z):- parent(Z,Y),parent(Y,X).
grand_pere(X,Z):- grand_parent(X,Z),homme(X).
grand_mere(X,Z):- grand_parent(X,Z),femme(X).
petit_fils(X,Z):- petit_enfant(X,Z),homme(X).
petite_fille(X,Z):- petit_enfant(X,Z),femme(Z).
frere_ou_soeur(X,Y):- pere(Z,X),pere(Z,Y),mere(Z,X),mere(Z,Y),X \= Y.
frere(X,Y):- frere_ou_soeur(X,Y),homme(X).
soeur(X,Y):- frere_ou_soeur(X,Y),femme(X).
oncle_ou_tante(X,Y):- frere_ou_soeur(X,Z),parent(Z,Y).
