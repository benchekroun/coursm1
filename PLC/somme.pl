
somme(X,Y,Z):- X is Y+Z.
 %attention : dans le predicat suivant, Y+Z est un terme, il ne permet pas d'evaluer la somme

somme2(X,Y,X+Y).