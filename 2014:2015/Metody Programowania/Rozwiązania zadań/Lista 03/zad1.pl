perm([],[]).

perm([H|T], X):-
	perm(T,Y),
	select(H,X,Y).