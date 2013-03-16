-module(ring).
-export([launch/4,init/3]).

splice(X,Y) ->
    X ! {next,self()},
    receive NX ->
        Y ! {next,self()},
        receive NY ->
            Y ! {set,NX,self()},
            X ! {set,NY,self()},
            receive ok -> ok end,
            receive ok -> ok end
        end
    end.

init(Mod,Fun,Uid) ->
    wait(Mod,Fun,Uid,self()).

wait(Mod,Fun,Uid,Next) ->
    receive
        {next,Who} -> Who ! Next, wait(Mod,Fun,Uid,Next) ;
        {set,NNext,Who} -> Who ! ok, wait(Mod,Fun,Uid,NNext) ;
        start -> Mod:Fun(Uid,Next)
    end.

create(Mod,Fun,Uid,1) ->
    Pid = spawn(?MODULE,init,[Mod,Fun,Uid]),
    {Pid,[Pid]} ;
create(Mod,Fun,Uid,N) ->
    N1 = N div 2,
    N2 = N-N1, 
    {P,A} = create(Mod,Fun,Uid,N1),
    {Q,B} = create(Mod,Fun,Uid+N1,N2),
    splice(P,Q),
    R = walk(P,random:uniform(N)),
    {R, B ++ A}.

walk(X,0) -> X ;
walk(X,N) ->
    X ! {next,self()},
    receive Z ->
        walk(Z,N-1)
    end.

launch(Mod,Fun,Uid,N) ->
    {X, L} = create(Mod,Fun,Uid,N),
    go(L),
    X.

go([]) -> ok ;
go([X|L]) -> X ! start, go(L).

