sublist(_,[]).

sublist([X|Y], [X|Z]):-
    sublist(Y,Z).

sublist([_|X],Y):-
    sublist(X,Y).