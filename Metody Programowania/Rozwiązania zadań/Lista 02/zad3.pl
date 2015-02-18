% 1) 
% ?- append(X,X,Y).
% X = Y, Y = [] 
% X = [_G1280],
% Y = [_G1280, _G1280] 
% X = [_G1280, _G1286],
% Y = [_G1280, _G1286, _G1280, _G1286] 
% .
% .
% .

% 2)
% ?- select(X,[a,b,c,d],[a,c,d]).
% X = b 
% false.

% 3)
% ?- append([a,b,c], X, [a,b,c,d,e]).
% X = [d, e].