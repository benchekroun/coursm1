/* derivee_formelle(F, X, FP) : F terme. X atom. FP (dit Fprime) terme dérivée formelle de F par X. */

derivee_formelle(F1 + F2, X, F1P + F2P) :-
	!,
	derivee_formelle(F1, X, F1P),
	derivee_formelle(F2, X, F2P).
	
derivee_formelle(F1 - F2, X, F1P - F2P) :-
	!,
	derivee_formelle(F1, X, F1P),
	derivee_formelle(F2, X, F2P).
	
derivee_formelle(F1 * F2, X, F1P * F2 + F1 * F2P) :-
	!,
	derivee_formelle(F1, X, F1P),
	derivee_formelle(F2, X, F2P).

derivee_formelle(F1 / F2, X, (F1P * F2 - F1 * F2P) / F2^2) :-
	!,
	derivee_formelle(F1, X, F1P),
	derivee_formelle(F2, X, F2P).

derivee_formelle(F ^ N, X, FP * N * F^N1) :-
	!,
	N1 is N - 1,
	derivee_formelle(F, X, FP).

derivee_formelle(-F, X, -FP) :-
	!,
	derivee_formelle(F, X, FP).

derivee_formelle(exp(F), X, exp(F) * FP) :-
	!,
	derivee_formelle(F, X, FP).

derivee_formelle(log(F), X, FP / F) :-
     	!,
	derivee_formelle(F, X, FP).

derivee_formelle(X, X, 1) :- !.	% Coupure obligatoire pour ne pas satisfaire la règle suivante lors du retour arrière.

derivee_formelle(C, X, 0).		% Dans ce cas, C est tout autre terme non prévu par les cas de notre prédicat. 
								% On le considère alors comme une constante!


/* simplifier(E, S) : E terme qui représente une expression. S sa forme simplifiée. */

simplifier(E1 + E2, R) :-
	number(E1),
	number(E2),
	!,
	R is E1 + E2.

simplifier(N + E, R) :-
	number(N),
	!,
	simplifier(E + N, R).

simplifier(E1 + E2, R) :-
	simplifier(E1, S1),
	simplifier(E2, S2),
	(E1 \== S1 ; E2 \== S2),
	!,
	simplifier(S1 + S2, R).

simplifier(E1 + (E2 + E3), R) :- % Associativité
	simplifier(E1 + E2, S),
	(S \== E1 + E2),
	!,
	simplifier(S + E3, R).

simplifier((E1 + E2) + E3, R) :- % Associativité
	simplifier(E2 + E3, S),
	(S \== E2 + E3),
	!,
	simplifier(E1 + S, R).

simplifier(E + 0, R) :-
	!,
	simplifier(E, R).

simplifier(E1 * E2, R) :-
	number(E1),
	number(E2),
	!,
	R is E1 * E2.

simplifier(E * N, R) :-
	number(N),
	!,
	simplifier(N * E, R).

simplifier(E1 * E2, R) :-
	simplifier(E1, S1),
	simplifier(E2, S2),
	(E1 \== S1 ; E2 \== S2),
	!,
	simplifier(S1 * S2, R).

simplifier(E1 * (E2 * E3), R) :- % Associativité
	simplifier(E1 * E2, S),
	(S \== E1 * E2),
	!,
	simplifier(S * E3, R).

simplifier(E1 * (E2 * E3), R) :- % Associativité
	simplifier(E1 * E2, S),
	(S \== E1 * E2),
	!,
	simplifier(S * E3, R).

simplifier(1 * E, R) :-
	!,
	simplifier(E, R).

simplifier(0 * E, 0) :-
	!.

simplifier(E1*X + E2*X, R) :-
	!,
	simplifier((E1 + E2) * X, R).
% rajout de l'élève Alexandre Masson
simplifier(N1 - N2, R) :-
	number(N1),
	number(N2),
	!,
	R is N1-N2.
% cas n - expression
simplifier(N - E, R) :-
	number(N),
	!,
	simplifier(-E,R1),
	simplifier(N + R1,R).
% cas ou c'est exp -n
simplifier(E - N, R) :-
	number(N),
	!,
	simplifier(E,R1),
	simplifier(R1 - N , R).

simplifier(-E,-R) :-
	!,
	simplifier(E,R).

simplifier(E1 / E2, E3 / E4) :-
	!,
	simplifier(E1,E3),
	simplifier(E2,E4),
	E4 \== 0.

% completer le predicat avec les symboles : -,/,log,^,...?

% En dernier :

simplifier(X, X).
