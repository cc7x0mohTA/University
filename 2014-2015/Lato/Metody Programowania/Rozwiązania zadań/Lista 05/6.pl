generujliste([],[]).
generujliste([H|L],[[H]|LL]):-
	generujliste(L,LL).

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


mss(L,W):-
	generujliste(L,LL),
	ms3(LL,W).

ms3(LL,W):-
	ms3(LL,W,[]).
ms3([],S,[S]):-!.
ms3([S],W,A):-
	ms3([S|A],W,[]).
ms3([],W,A):-
	ms3(A,W,[]).

ms3([H1,H2|LL],W,A):-
	merge(H1,H2,X),
	ms3(LL,W,[X|A]).
