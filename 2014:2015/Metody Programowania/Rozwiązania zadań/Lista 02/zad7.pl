perm([],[]).

perm(L, [X|Y]):-
    select(X,L,Z),
    perm(Z, Y).