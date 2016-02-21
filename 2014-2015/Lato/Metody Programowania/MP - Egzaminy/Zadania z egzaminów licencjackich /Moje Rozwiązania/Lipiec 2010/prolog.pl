% Bartosz Jan Bednarczyk, 18.06.2015

% a)

pom([]).
pom([(-1)|T]) :- pom(T).
pom([1|T]) :- pom(T).

allMult(L, N) :- length(L, N), pom(L).

% b)

dotProd([], [], X, X).

dotProd([H1|T1], [H2|T2], A, B) :-
	A1 is A + H1*H2,
	dotProd(T1, T2, A1, B).

dotProd(L1, L2, X) :- dotProd(L1, L2, 0, X).
