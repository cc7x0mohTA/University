import Control.Monad 
import Data.List 

perm [] = [[]]
perm (x:xs) = concatMap (insert' x) (perm xs)

perm2 [] = [[]]
perm2 (x:xs) = [z | ys<-perm2 xs, z <- insert' x ys ]

perm3 [] = return []
perm3 (x:xs) = do
		ys <- perm3 xs
		zs <- insert' x ys
		return zs

insert' x [] = [[x]] 
insert' x l@(y:ys) = [x:l] ++ (map (y:) $ insert' x ys)
/Users/bartoszbednarczyk/Desktop/Lista 12/zad2.hs
/Users/bartoszbednarczyk/Desktop/Lista 12/zad3.hs
/Users/bartoszbednarczyk/Desktop/Lista 12/zad5.hs
/Users/bartoszbednarczyk/Desktop/Lista 12/zad6.hi
/Users/bartoszbednarczyk/Desktop/Lista 12/zad6.hs
/Users/bartoszbednarczyk/Desktop/Lista 12/zad7.hs