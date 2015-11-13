%dla stosu
put(E,S,[E|S]).
get([H|T],H,T).
empty([]).

addall(Element, Goal, Stack, Rest):-
  findall(Element, Goal, List),
  putall(List, Stack, Rest).

putall([],Rest,Rest).
putall([Head|Tail],Stack,Rest):-
  put(Head,Stack,NewStack),
  putall(Tail,NewStack,Rest).


%graph
droga(_, _, Res,[], Res).
droga(Poczatek, Koniec, Bylem, Sasiedzi, Res):-

