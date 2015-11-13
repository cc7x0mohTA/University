%appn z otwart¹ struktur¹ danych
appn([Res],Res).
appn([H1,H2|T],X):-
	append(H1,H2,H),
	appn([H|T],X).
