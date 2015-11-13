dalsze(X,0,X):-!.
dalsze([_|X],N,Y):-
	NN is N-1,
	dalsze(X,NN,Y).

merge([], List, List):-
	!.
merge(List, [], List):-
	!.
merge([Head1|Tail1], [Head2|Tail2], [Head1|Merged]):-
	Head1 =< Head2,
	!,
	merge(Tail1, [Head2|Tail2], Merged).
merge([Head1|Tail1], [Head2|Tail2], [Head2|Merged]):-
	merge([Head1|Tail1], Tail2, Merged).


ms2(_,0,[]):-!.
ms2([H|_],1,[H]):-!.
ms2([A],_,[A]).

ms2(X,N,Y):-
	N1 is N div 2,
	N2 is N-N1,
	ms2(X,N1,YY),
	dalsze(X,N1,Z),
	ms2(Z,N2,ZZ),
	merge(YY,ZZ,Y).
