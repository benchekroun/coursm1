-module(palindrome).
-export([go/1,cell/3]).

%% Reconnaissance de palindrome de longueur impaire sur un anneau bidirectionnel.
%% Pour un mot de longeur 2n+1, l'anneau est de longeur 2n+2.
%% Un noeud démarre dans l'état border, sans lettre.
%% Les autres noeuds reçoivent chacun une lettre et démarrent dans l'état letter.
%% ainsi le mot abbabba est codé #abbabba où # représente le bord du mot.

cell(L, R, 0) -> border(L, R) ;
cell(L, R, A) -> letter(L, R, A).

go(S) -> 
    register(monitor,self()),
    theWho = spawn(log,afficherEtBoucler,[]),
    biring:launch(biring:addproxy(log,miseEnLog,theWho,biring:uniform(?MODULE, cell, [0] ++ S))),
    receive
        palindrome -> unregister(monitor), palindrome ;
        notapalindrome -> unregister(monitor), notapalindrome     
    end.

absorb() ->
    receive _ -> ok end.

border(L, R) ->
    L ! {left, stop},
    R ! {right, stop},
    absorb(),
    absorb().

letter(L, R, A) ->
    L ! {left, A},
    R ! {right, A},
    xchange(L, R, good).

xchange(L, R, St) ->
    receive
        {left, stop} ->
            receive
                {right, stop} when St == good ->
                    io:format("le mot est un palindrome.~n"),
                    monitor ! palindrome ;
                {right, stop} ->
                    io:format("le mot n'est pas un palindrome.~n"),
                    monitor ! notapalindrome ;
                {right, _} ->
                    L ! {left, stop},
                    absorb()
            end ;
        {left, A} ->
            receive
                {right, stop} ->
                    R ! {right, stop},
                    absorb() ;
                {right, A} ->
                    L ! {left, A},
                    R ! {right, A},
                    xchange(L, R, St) ;
                {right, B} ->
                    L ! {left, A},
                    R ! {right, B},
                    xchange(L, R, bad)
            end
    end.

