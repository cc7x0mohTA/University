% insert(Tree, Value, Result).

flatten(leaf, []).
flatten(node(L,E,R),List):-
	flatten(L,List1),
	flatten(R,List2),
	append(List1,[E|List2],List).

insert(leaf, Value, node(leaf, Value, leaf)).

insert(node(Left, NValue, Right), Value, node(Left, NValue, InsertedRight)):-
Value >= NValue,
insert(Right, Value, InsertedRight).

insert(node(Left, NValue, Right), Value, node(InsertedLeft, NValue, Right)):-
Value < NValue,
insert(Left, Value, InsertedLeft).




treesort(List, SortedList):-
treesort(List, SortedTree, leaf),
flatten(SortedTree, SortedList).
treesort([], SortedTree, SortedTree).
treesort([H|T], SortedTree, Acc):-
insert(Acc, H, NextAcc),
treesort(T, SortedTree, NextAcc).












