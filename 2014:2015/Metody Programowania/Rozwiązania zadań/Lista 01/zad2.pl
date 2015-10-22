mily(X):-
	czlowiek(X),
	odwiedzazoo(X).

stykasie(X, Y):-
	mieszkawzoo(X),
	zwierze(X),
	czlowiek(Y),
	odwiedzazoo(Y).

szczesliwe(X):-
	stykasie(X,Y),
	czlowiek(Y),
	mily(Y).

nie_smok(X):-
	szczesliwe(X),
	mieszkawzoo(X).

zwierze(X):-
	smok(X).

czlowiek(rychu).
odwiedza_zoo(rychu).
smok(peja).
mieszkawzoo(zbyszek).