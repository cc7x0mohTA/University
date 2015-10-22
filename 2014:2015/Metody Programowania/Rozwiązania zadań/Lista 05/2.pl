%czy obiekt jest lista?
list([]).
list([_|X]):-
	list(X).

%z akumulatorem:

%baza:
flatten([],Acc, Acc).

%krok:
flatten([H|T], Wynik, Acc):-
	list(H),!,
	flatten(H,H1),
	append(Acc,H1,Acc1),
	flatten(T,Wynik,Acc1).
flatten([H|T], Wynik, Acc):-
	flatten(T, Wynik, [H|Acc]).

%flatten/2.
flatten(X,Y):-
	flatten(X,Y,[]).
