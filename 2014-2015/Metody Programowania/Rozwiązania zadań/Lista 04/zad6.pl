sublist(_,[]).
sublist([H|T],[H|S]):-
sublist(T,S).
sublist([_|T],S):-
sublist(T,S).

concat_number(Digits, Num):-
concat_number(Digits, 0, Num).

concat_number([], Res, Res).
concat_number([H|T], Acc, Res):-
NextAcc is (Acc * 10) + H,
concat_number(T, NextAcc, Res).
