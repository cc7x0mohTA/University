word3(0) --> "".
word3(X) --> "a", word3(Y),{X is Y + 1}, "b".
