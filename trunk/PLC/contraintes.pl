probleme1(X,Y):-
	X #= Y +10,
	X+5 #= 2*(Y+5).


probleme2(P,E,J) :-
	fd_domain(P,1,100),
	fd_domain(E,1,100),
	fd_domain(J,1,100),
	P #= 3*J,
	P*P #= E*J*J,
	2*(P-1) #= 2*((E+1)+(J+1)+(J+1)),fd_labeling(P).

probleme3(S,E,N,D,M,O,R,Y) :-
	fd_domain([S,E,N,D,M,O,R,Y],0,9),
	1000*S + 100*E + 10*N + D + 1000*M + 100 *O + 10*R+E #= 10000*M+1000*O+100*N + 10 *E +Y, S#\= 0, M#\= 0,fd_all_different([S,E,N,D,M,O,R,Y]),fd_labeling([S,E,N,D,M,O,R,Y]).

probleme4(Roses,Lilas,Lys,Rhododendrons,Essaim) :-
	5*Roses #= Essaim,
	3*Lilas #= Essaim,
	3*(Lilas - Roses) #= Lys,
	Rhododendrons #= 1,
	Essaim #= Roses + Lilas + Lys + Rhododendrons.

probleme5(A,B,C,D,E,F,G,H,I) :-
	fd_domain([A,B,C,D,E,F,G,H,I],1,9),
	fd_all_different([A,B,C,D,E,F,G,H,I]),
	% (A/(10*B+C)) + (D/(10*E+F)) + (G/(10*H+I)) #= 1.
	EF #= 10*E +F,
	HI #= 10*H +I,
	BC #= 10*B+C,
	X #= A*EF*HI,
	Y #= D*BC*HI,
	Z #= G*BC*EF,
	RES #= BC*EF*HI,
	X+Y+Z #= RES,
	fd_labeling([A,B,C,D,E,F,G,H,I]).

