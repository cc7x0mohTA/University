% rev(X, Acc, Y, X2, Acc2, Y2).  

rev(X,Y):- rev(X, [], Y, Y, [], X).

rev([],A,A,_,_,_).
rev(_,_,_,[],A,A).

rev([H|T], A, Y, [G|S], B, Z) :-
	rev(T, [H|A], Y, S, [G|B], Z), !.