mirror(leaf, leaf).
mirror(node(L,E,R),X):-
	mirror(L,R1),
	mirror(R,L1),
	X=node(L1,E,R1).

flatten(leaf, []).
flatten(node(L,E,R),List):-
	flatten(R,List1),
	flatten(L,List2),
	append(List1,[E|List2],List).
