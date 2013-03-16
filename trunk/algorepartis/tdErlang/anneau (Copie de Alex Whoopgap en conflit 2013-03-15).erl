-module(anneau). %anneau nom du fichier
-export([create/4,init/3,launch/4]).

         
%fonction, qui echange les voisins de deux noeuds
%sert a raccorder un  noeud seul à l'anneau
splice(X,Y) ->
X ! {next,self()},
receive
	NX -> 
		Y ! {next,self()}
	receive
		NY -> 
			X ! {set,NY},
			Y ! {set,NX};
	end
end.

%marche aléatoire
walk(Pid,0) -> Pid;
walk(Pid,N) ->   
	Pid ! {next , self()}
	receive
		Next -> walk(Next,N-1)
	end.

%create anneau de taille N
%cas facile n=1
create(Mod,Fun,Uid,1)->
	Pid = spawn(?module,init,[Mod,Fun,UID]),
	{Pid,[Pid]};
create(Mod, Fun, Uid,N) ->
	%on creer un anneau de n-1
	{X,L} = create(Mod,Fun,Uid+1,N-1),
	%on cree le noueud Uid
	{Y,_} = create(Mod,Fun,Uid,1),
	%on splice pour l'ajouter dnas l'anneau
	splice(X,Y),
	%on choisit un voisin aléatoire.
	Z=walk(X,random:uniform(N)),{Z,Y|L}.



%notre processus s'initialise en appelant wait pour attendre le start
init(Mod,Fun,Uid)->
	wait(Mod,Fun,Uid,self());

%fonction d'attente entre l'envoi des messages
wait(Mod,Fun,Uid,Next)->
receive 
	
	start -> Mod:Fun(Uid,Next);
	%next est un requete de qui ets ton next et c'est Who qui te le demande, on envoie donc a who notre next
	{next,Who} -> Who!Next;
	{set,NNext} -> wait(Mod,Fun,Uid,NNext);
	X -> self() ! start , self() ! X;

end.
