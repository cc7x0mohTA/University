halve(List, Left, Right):-
	halve(List, List, Left, Right).

halve(Right, [], [], Right):-
	!.
halve(Right, [_], [], Right):-
	!.
halve([Head|Tail], [_,_|Bound], [Head|Left], Right):-
	halve(Tail, Bound, Left, Right).


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

% mergesort(List, Sorted).
mergeSort([X],[X]):-!.
mergeSort(List,Sorted):-
	halve(List,Left,Right),
	mergeSort(Left, SortedLeft),
	mergeSort(Right,SortedRight),
	merge(SortedLeft, SortedRight,Sorted).
