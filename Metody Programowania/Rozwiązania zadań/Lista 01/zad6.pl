polaczenie(wroclaw, warszawa).
polaczenie(wroclaw, krakow).
polaczenie(wroclaw, szczecin).
polaczenie(szczecin, lublin).
polaczenie(szczecin, gniezno).
polaczenie(warszawa, katowice).
polaczenie(gniezno, gliwice).
polaczenie(lublin, gliwice).

% to moze nie dzialac czy graf zawiera cykl

connection(X,Y):-
	polaczenie(X,Y).

connection(X,Y):-
	polaczenie(X,Z),
	connection(Z,Y).

% ?- polaczenie(wroclaw,lublin).
% false.

% ?- polaczenie(wroclaw, X).
% X = warszawa 
% X = krakow 
% X = szczecin.

% ?- polaczenie(X,Y), polaczenie(Y,gliwice).
% X = szczecin,
% Y = lublin 
% X = szczecin,
% Y = gniezno 
% false.

% ?- polaczenie(X,Y), polaczenie(Y, Z), polaczenie(Z,gliwice).
% X = wroclaw,
% Y = szczecin,
% Z = lublin 
% X = wroclaw,
% Y = szczecin,
% Z = gniezno 
% false.
