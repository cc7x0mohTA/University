%baza wiedzy

polaczenie(wroclaw, warszawa).
polaczenie(wroclaw, krakow).
polaczenie(wroclaw, szczecin).
polaczenie(szczecin, lublin).
polaczenie(szczecin, gniezno).
polaczenie(warszawa, katowice).
polaczenie(gniezno, gliwice).
polaczenie(lublin, gliwice).
polaczenie(katowice, szczecin).

%program:
trip(M,M,A,A).
trip(Poczatek, Koniec, Trasa, A):-
	polaczenie(X,Koniec),
	\+ member(X,A),
	A1=[X|A],
	trip(Poczatek, X, Trasa, A1).

trip(P,K,T):-
	trip(P,K,T,[K]).
