ptak(_) :- fail.
ryba(_) :- fail.
dzdzownica(_) :- fail.

kot(my_cat).
przyjaciele(me, my_cat).

lubi(X,Y) :- ptak(X), dzdzownica(Y).
lubi(X,Y) :- kot(X), ryba(Y).
lubi(X,Y) :- przyjaciele(X,Y).
lubi(X,Y) :- przyjaciele(Y,X).

zjada(my_cat, X) :- lubi(my_cat, X).

% zjada(my_cat, X).