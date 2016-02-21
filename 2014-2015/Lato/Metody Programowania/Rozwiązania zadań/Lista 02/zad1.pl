Zad 1

?- append(X,Y,[a,b,c]).
X = [],
Y = [a, b, c]
X = [a],
Y = [b, c]
X = [a, b],
Y = [c]
X = [a, b, c],
Y = []
false.