even([]).
even([_,_|X]):- even(X).

palindrom(X):-
	Y = X,
	reverse(X,Y).

singleton([_]).