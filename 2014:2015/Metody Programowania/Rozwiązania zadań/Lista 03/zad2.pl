exp(Base,Exp,Res):-
	Res is Base^Exp.

filter([],[]).

filter([H|T],[H|S]):-
	H >= 0,
	!,
	filter(T,S).

filter([H|T],S):-
	H < 0,
	filter(T,S).

count(_, [], 0).

count(X, [X|L], N):-
	count(X, L, C), !,
	N is C+1.

count(X, [_|L], N):-
	count(X, L, N).