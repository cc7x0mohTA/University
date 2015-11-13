length([],A,A).
length([_|T],N,A):-
	A1 is A+1,
	length(T,N,A1).
length(X,N):-
	length(X,N,0).
