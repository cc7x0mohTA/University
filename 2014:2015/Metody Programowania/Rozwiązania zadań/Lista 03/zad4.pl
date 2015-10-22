leng([],0):-!.
leng([_|S],X):-
	length(S,X1),
	X is X1+1.
