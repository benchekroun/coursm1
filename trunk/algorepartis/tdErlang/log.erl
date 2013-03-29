-module(log).
-export([miseEnLog/4,afficherEtBoucler/0]).

miseEnLog(Node,Left,Right,Who)->
	receive
		{left,Msg} -> Who ! {Node,left,Msg}, Left ! {msg,Msg};
		{right,Msg} -> Who ! {Node,right,Msg},Right ! {msg,Msg};
		{msg,Msg} -> Node ! Msg
	end,
	miseEnLog(Node,Left,Right,Who).

afficherEtBoucler() ->
	receive
		{Node,Cote,Msg} -> io:format("~w send ~w to the ~w~n",[Node,Msg,Cote])
	end,
	afficherEtBoucler().
