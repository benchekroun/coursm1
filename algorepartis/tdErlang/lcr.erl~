-module(lcr).
-export([lcr/2,go/1]).

lcr(Uid,Next) ->
	Next ! Uid,
	loop(Uid,Next).

go(N) ->
	anneau:launch(?MODULE,LCR,1,N).

loop(Uid,Next) ->
receive
	Stop -> Next ! Stop, io:format("[~w] stops ~n",[Uid]);
	start -> loop(Uid,Next);
	Val when Val >Uid ->
		io:format("[~w] got ~w.~n",[Uid,Val]),
		Next ! Val,
		loop(Uid,Next);
	Val when Val == Uid ->
		io:format("[~w] got ~w.~n",[Uid,Val]),leader(Uid,Next);
	Val −> io:format("[~w] got ~w.~n",[Uid,Val]),loop(Uid,Next)	
end.

leader(Uid,Next) ->
	io:format("Youhou ~w.~n",[Uid,Val]),	
	Next ! Stop,
	receive
		Stop -> ok
	end.


peterson(Uid,Next) ->
Next ! Uid,
receive
	start -> peterson(Uid,Next);
	Uid2 -> Next ! Uid2,
	receive
		Uid3 when (Uid2>Uid) and (Uid2 >Uid3) ->
				peterson(Uid2,Next);
		Uid3 when Uid == Uid2 ->
			leader(Uid,Next);
		_ -> relay(Uid,Next)
	end
end.

relay(Uid,Next) ->
receive
	MSG -> Next ! MSG;
	Stop -> Next ! Stop, io:format("[~w] stops ~n",[Uid]);
end.
