-module(peterson).
-export([peterson/2,go/1]).

%%
%% Leader election on an unidirectional ring.
%% Peterson's algorithm.
%%

relay(Uid,Next) ->
    receive
        {stop, Leader} ->
            io:format("[~w] stops (leader ~w).~n",[Uid,Leader]),
            Next ! {stop, Leader} ;
        X ->
            %% io:format("[~w] forwards ~w.~n",[Uid,X]),
            Next ! X,
            relay(Uid,Next)
    end.

peterson(Uid,Next) -> peterson(Uid,Uid,Next).

peterson(Ouid,Uid,Next) ->
    Next ! Uid,
    receive
        Uid2 ->
            Next ! Uid2,
            receive
                Uid3 when (Uid2 > Uid3) and (Uid2 > Uid) ->
                    io:format("[~w] as ~w got ~w and ~w, acting as ~w.~n",[Ouid,Uid,Uid2,Uid3,Uid2]),
                    peterson(Ouid,Uid2,Next) ;
                Uid3 when Uid == Uid2 ->
                    io:format("[~w] as ~w got ~w and ~w, leader!~n",[Ouid,Uid,Uid2,Uid3]),
                    leader(Uid,Next) ;
                Uid3 ->
                    io:format("[~w] as ~w got ~w and ~w, relay.~n",[Ouid,Uid,Uid2,Uid3]),
                    relay(Ouid,Next)
            end
    end.

leader(Uid,Next) ->
    Next ! {stop, Uid},
    receive
        {stop, _} ->
            io:format("[~w] stops.~n",[Uid]),
            monitor ! theend
    end.

go(N) ->
    register(monitor,self()),
    ring:launch(?MODULE,peterson,1,N),
    receive
        theend -> ok
    end.

