~module(ab).
~export([start/0,alice/1, bob/0]).

start() ->
	Bob = spawn(ab,bob,[]),
	Alice = spawn(ab,alice,[Bob]),
	Alice.


alice(Bob) -> 

receive
	go ->
		Bob ! {ping,self()},
		alice(Bob) ;
	pong ->
		io:format("pong~n")
end.

bob() ->
receive
 	{ping,Alice} ->
 		io:format("ping~n"),
		Alice ! pong
end.
