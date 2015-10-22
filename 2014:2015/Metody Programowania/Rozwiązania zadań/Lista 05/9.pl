sum(X, Y, Suma):-
    integer(X),
    integer(Y),
    !,
    Suma is X + Y.
sum(X, Y, Suma):-
    integer(X),
    integer(Suma),
    !,
    Y is Suma - X.
sum(X, Y, Suma):-
    integer(Y),
    integer(Suma),
    !,
    X is Suma - Y.


nat(1).
nat(X):-
    nat(Y),
    X is Y + 1.

zas(Zasieg, Zasieg).
zas(Zasieg, Y):-
    Y is -Zasieg.
zas(Zasieg, X):-
    Zasieg2 is Zasieg - 1,
    Zasieg2 >= 0,
    zas(Zasieg2, X).


sum(X, Y, Suma):-
    nat(N),
    select(Tryb, [1, -1], _),
    select(Z1, [X, Y], [Z2]),
    Z1 is N * Tryb,
    zas(N, Z2),
    Suma is X + Y.





