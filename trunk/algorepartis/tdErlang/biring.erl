-module(biring).
-export([launch/1,uniform/3,init/0,proxy/3,addproxy/4]).

%creation de proxy
proxy(Left,Right,{ModP,FunP,AP,Mod,Fun,A})->
	%on creer les deux node marqueurs left et right
	NL = spawn(?MODULE,mark,[Left,self()]),
	NR = spawn(?MODULE,mark,[Right,self()]),
	%on lance l'execution du node,  avec NL, et NR en voisin
	N = spawn(Mod,Fun,[NL,NR,A]),

	%lancer l'execution du proxy 
	ModP:FunP(N,Left,Right,AP).



%ajouter un proxy à un argument de launch
addproxy(ModP,FunP,AP,List)->
 lists:map(fun({Mod,Fun,A})->{ModP,FunP,AP,Mod,Fun,A} end, List).

%creation
create(1) ->
    Pid = spawn(?MODULE,init,[]),
    {Pid,[Pid]} ;
create(N) ->
    N1 = N div 2,
    N2 = N-N1, 
    {P,A} = create(N1),
    {Q,B} = create(N2),
    splice(P,Q),
    R = walk(P,random:uniform(N)),
    {R, B ++ A}.

launch(List) ->
	% penser à donner les valuer à chaque node
	N = length(List),
   {X, L} = create(N),
	%initialiser les valeurs des anneaux
	%populate(X,List (liste des triplets a affecter à chacun des node)
	populate(X,List),
    go(L),
    X.

%déploie les modules,fonctions et attributs sur les nodes
populate(_,[]) -> ok;
populate(X,[Y|Q]) ->
	X ! {setA,Y,self()},
	receive ok -> ok end,
	Suiv = walk(X,1),
	populate(Suiv,Q).



go([]) -> ok ;
go([X|L]) -> X ! start, go(L).

uniform(Mod,Fun,List) ->
    lists:map(fun(X) -> {Mod,Fun,X} end, List).

%marquer un messages avec gauche ou drooite
mark(A,To) ->
	receive
		X -> To ! {A,X}
	end,
	mark(A,To).

%se déplacer de N cases a droite
walk(X,0) -> X ;
walk(X,N) ->
    X ! {right,self()},
    receive Z ->
        walk(Z,N-1)
    end.


%changer des voisins des noeuds (raccordements)
splice(X,Y) ->
            X ! {left,self()},
		receive LX ->
			Y ! {left,self()},
				receive LY ->
					X ! {setL, LY, self()},
					Y ! {setL, LX,self()},
					LX ! {setR, Y, self()},
					LY ! {setR,X,self()},
					receive ok -> ok end,
            				receive ok -> ok end,
					receive ok -> ok end,
            				receive ok -> ok end
				end
		end.
%DONE

%inti du mode
init() ->
    wait(null,null,self(),self(),null). %DONE

%fonction d'attente des messages
wait(Mod,Fun,Left,Right,Val) ->
    receive
	%acces Left
	{left,Who} -> Who ! Left, wait(Mod,Fun,Left,Right,Val);
	%acces Right
	{right,Who} -> Who ! Right, wait(Mod,Fun,Left,Right,Val);
	%changer le left 
        {setL,NLeft,Who} -> Who ! ok, wait(Mod,Fun,NLeft,Right,Val) ;
	%changer le right
	{setR,Nright,Who} -> Who! ok, wait(Mod,Fun,Left,Nright,Val);
	%Changer la valeur
	{setA,{NMod,NFun,NVal},Who} -> Who! ok, wait(NMod,NFun,Left,Right,NVal);
	%commencer l'exécution
        start -> Mod:Fun(Left,Right,Val)
    end.
%DONE
