%dom(wlasiciel, numer, kolor, zwierze, papierosy, trunek)
sasiaduje(X,Y):-
                X=1,Y=2;
		X=2,Y=3;
		X=3,Y=5;
		X=4,Y=5.
sasiaduje(X,Y):-
                sasiaduje(Y,X).
%2
dom(anglik, _, czerwony,_,_,_).
%3
dom(hiszpan,_,_,pies,_,_).
%4
dom(_,_, zielony,_,_,kawa).
%5
dom(ukrainiec,_,_,_,_,herbata).
%6
dom(_,X,zielony,_,_,_):-
             dom(_,Y,bialy,_,_,_),
	     sasiaduje(X,Y).

%7
dom(_,_,_,waz, winston,_).
%8
dom(_,_, zolty,_, kool,_).
%9
dom(_,3,_,_,_,mleko).
%10
dom(norweg,1,_,_,_,_).
%11
dom(_,X,_,_,cheterfild,_):-
              dom(_,Y,_,lis,_,_), sasiad(X,Y).
%12
dom(_,X,_,kon,_,_):-
	      dom(_,Y,_,_,kool,_), sasiad(X,Y).
%13
dom(_,_,_,_,lucky,sok).
%14
dom(japonczyk,_,_,_,kent,_).
%15
dom(norweg,X,_,_,_,_):-
               dom(_,Y,niebieski,_,_,_), sasiad(X,Y).
