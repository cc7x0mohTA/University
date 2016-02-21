wariacje(Len,List,Acc,[H|Acc]):-
	Len=1,!,
	member(H, List).
wariacje(Len,List,Acc,Res):-
	member(H,List),
	Len1 is Len-1,
	wariacje(Len1, List, [H|Acc], Res).

wariacje(Len, List, Res):-
	wariacje(Len, List, [], Res).

decimal(L,W):-
	decimal(L,[],W).
decimal(0, Acc, Res):-
  !,
  Acc = Res.
decimal(Num, Acc, Res):-
  CurrentDigit is Num mod 10,
  NewNum is Num // 10,
  decimal(NewNum, [CurrentDigit|Acc], Res).

cn(D,N):-
	cn(D,0,X),
	N is X.
cn([],X,X).
cn([H|T],Acc,Res):-
	Acc1=10*Acc+H,
	cn(T,Acc1,Res).



zgodneZeSchematem([Cyfra],[c]):-
	member(Cyfra,[1,3,5,7,9]),!.
zgodneZeSchematem([Cyfra],[s]):-
	member(Cyfra,[0,2,4,6,8]),!.

zgodneZeSchematem([Cyfra|Reszta],[c|T]):-
	member(Cyfra,[1,3,5,7,9]),
	zgodneZeSchematem(Reszta,T),!.

zgodneZeSchematem([Cyfra|Reszta],[s|T]):-

	    member(Cyfra,[0,2,4,6,8]),
	    zgodneZeSchematem(Reszta,T),!.

zgodne(Liczba,Wzor):-
	decimal(Liczba,Lista),
	zgodneZeSchematem(Lista,Wzor).


program([P,D|T], Wynik):-
	length(P,LenP),
	length(D, LenD),
	wariacja(LenP,
