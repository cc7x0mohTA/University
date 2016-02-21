sibling(X, Y):- % X jest rodzenstwem Y
	parent(Z, X), parent(Z, Y).

sister(X, Y):-	% X jest siostra Y
	female(X), sibling(X,Y).

grandson(X,Y):- % X jest wnukiem Y
	parent(Z, X), parent(Y,Z).

cousin(X,Y):- % X jest kuzynem Y
	male(X), parent(Z, Y), parent(W, X), sibling(W,Z).

descendant(X,Y):- % Czy X jest potomkiem Y?
	parent(Y,X).

descendant(X,Y):- % Czy X jest potomkiem Y?
	parent(Y,Z), descendant(X,Z).

is_mother(X):- % Czy X jest matka?
	female(X), parent(X, _).

is_father(X):- % Czy X jest ojcem?
	male(X), parent(X, _).

% X jest rodzicem Y

parent(adam, helen).
parent(adam, ivonne).
parent(adam, anna).
parent(eve, helen).
parent(eve, ivonne).
parent(eve, anna).
parent(helen, joshua).
parent(john, joshua).
parent(ivonne, david).
male(adam).
male(john).
male(joshua).
male(david).
male(mark).
female(eve).
female(helen).
female(ivonne).
female(anna).

% descendant(john, mark).
% false.

% ?- descendant(X,adam).
% X = helen 
% X = ivonne 
% X = anna 
% X = joshua 
% X = david 

% ?- sister(X, ivonne).
% X = helen 
% X = helen 
% X = ivonne 
% X = ivonne 
% X = anna 
% X = anna.


% ?- cousin(X,Y).
% X = Y, Y = joshua 
% X = Y, Y = joshua 
% X = joshua,
% Y = david 
% X = joshua,
% Y = david 
% X = david,
% Y = joshua 
% X = david,
% Y = joshua 
% X = Y, Y = david 
% X = Y, Y = david 
% false.

