-module(log).
-export([miseEnLog/4,afficherEtBoucler/0]).
%pour les horloges, on change Who −> {Who,Time}
miseEnLog(Node,Left,Right,{Who,T})->
	receive
		{left,Msg} -> Who ! {T,Node,left,Msg}, Left ! {msg,Msg,T}, NT= T+1;
		{right,Msg} -> Who ! {Node,right,Msg},Right ! {msg,Msg,T}, NT= T+1;
		{msg,Msg,TT} -> Node ! Msg, NT = max(T,TT)+1
	end,
	miseEnLog(Node,Left,Right,{Who,NT}).

afficherEtBoucler() ->
	receive
		{Node,Cote,Msg} -> io:format("~w send ~w to the ~w~n",[Node,Msg,Cote])
	end,
	afficherEtBoucler().
