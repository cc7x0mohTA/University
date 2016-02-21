% Stos w Prologu

put_S(E, L, [E|L]).	% dodajemy nowy element na poczatek listy
get_S([H|T], H, T).	% usuwamy pierwszy element z listy
empty_S([]).

addall_S(E, G, S, R):-
	findall(E, G, L),	% znajdz wszystkie takie E, żę spełnia G i umieść w L
	append(L, S, R). 	% dodaj L na początek S - dostajemy nowy stos R

% Kolejka w Prologu (na listach różnicowych)

empty(X-X).
get([H|T]-X,H,T-X).

snoc(X-[E|Y],E,X-Y).
put(L, E, S) :- snoc(L, E, S).

addAll(E,G,X-Y,X-Z):-
    findall(E,G,Y,Z).
