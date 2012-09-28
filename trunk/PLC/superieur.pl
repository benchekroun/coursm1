
/* le plus grand de deux nombres */
max2(X,Y,R) :- X>=Y, R=X.
max2(X,Y,R) :- X<Y, R=Y.

/*max de trois valeurs*/
max3(X,Y,Z,R):-
	(max2(X,Y,R),max2(X,Z,R));
	(max2(Y,X,R),max2(Y,Z,R));
	(max2(Z,X,R),max2(Z,Y,R)).