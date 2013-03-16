-module(lcr).
-export([lcr/2,go/1]).

%%
%% Leader election on an unidirectional ring.
%% LCR algorithm.
%%

lcr(Uid,Next) ->
    Next ! Uid,
    loop(Uid,Next).

loop(Uid,Next) ->
    receive
        {stop, Leader} ->
            io:format("[~w] stops (leader ~w).~n",[Uid,Leader]),
            Next ! {stop, Leader} ;
        Val when Val > Uid ->
            io:format("[~w] forwarding ~w.~n",[Uid,Val]),
            Next ! Val,
            loop(Uid,Next) ;
        Val when Val == Uid ->
            io:format("[~w] leader!~n",[Uid]),
            leader(Uid,Next) ;
        Val ->
            %% io:format("[~w] got ~w.~n",[Uid,Val]),
            loop(Uid,Next)
    end.

leader(Uid,Next) ->
    Next ! {stop, self()},
    receive
        {stop, _} ->
            io:format("[~w] stops.~n",[Uid]),
            monitor ! theend
    end.

go(N) ->
    register(monitor,self()),
    ring:launch(?MODULE,lcr,1,N),
    receive
        theend -> ok
    end.
