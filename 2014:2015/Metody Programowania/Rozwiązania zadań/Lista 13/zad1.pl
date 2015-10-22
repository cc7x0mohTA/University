% generowanie listy 0...n-1

gen(N, L) :-
	M is N-1,
	findall(X, between(0,M,X), L).

% Zipowanie z dzialaniem
% za ostatni argument wstawiamy 1 gdy chcemy +, a -1 gdy -.

zipWith([], [], [], _).
zipWith([X|Xs], [Y|Ys], [Z|Zs], Sign):-
        Z is X + Sign * Y,
        zipWith(Xs, Ys, Zs, Sign).

% Przepisany check z haskella
% Sort potrzebny po to bo on usuwa duplikaty :)

check(L, Sign, X) :-
	length(L, SizeL),
	gen(SizeL, L1),
	zipWith(L, L1, L2, Sign),
	sort(L2, L3),
	length(L3, X).

% Tez przepisane z haskella

generate(N, Solution) :-
	gen(N, Xs),
	permutation(Xs, Solution),
	check(Solution, 1, N), check(Solution, -1, N).
