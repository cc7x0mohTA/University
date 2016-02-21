
czy_podciag(Lista1, Lista2) :-
	append(A, _, Lista1),
	append(_, X, A),
	append(B, _, Lista2),
	append(_, X, B),
	X = [_,_,_].

succ([],[1]):-!.
succ([0|T], [1|T]):-!.
succ([1|T], [0|W]):-
	succ(T,W).