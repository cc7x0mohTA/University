import Control.Monad 
import Data.List 

perms [] = [[]]
perms xs = concatMap (\x -> map (x:) (perms $ delete x xs) ) xs


perms2 [] = [[]]
perms2 xs = [y:ys | y <- xs, ys <- perms2 $ delete y xs]

perms3 [] = return []
perms3 xs = do
	y <- xs
	ys <- perms3 $ delete y xs
	return (y:ys)