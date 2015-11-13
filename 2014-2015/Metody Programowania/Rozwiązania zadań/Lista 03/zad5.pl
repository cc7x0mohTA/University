insert([],H,[H]).
insert([H|L],Elem, Res):-
	Elem=<H, !,
	Res=[Elem,H|L].
insert([H|L],Elem, Res):-
	insert(L,Elem,Res1),
	Res=[H|Res1].

ins_sort([],[]).
ins_sort([H|L],S):-
	ins_sort(L,S1),
	insert(S1,H,S).
