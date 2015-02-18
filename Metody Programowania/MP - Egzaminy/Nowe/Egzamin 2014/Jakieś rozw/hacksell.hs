--foldr2 :: (a->b->c->c) -> c -> [a] -> [b] -> c
--foldr2 f c [] [] = c
--foldr2 f c (x:xs) (y:ys) = f x y (foldr2 f c xs ys)

--zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
--zipWith' f = foldr2 (\ a b c -> (f a b) : c ) []

-- ----------

import Control.Monad

f :: [a] -> [[a]]
f [] = return []
f (x:xs) = do
		ys <- f xs
		return (x:ys) `mplus` 
			return ys



f' :: [a] -> [[a]]
f' [] = [[]]
f' (x:xs) = concatMap (\ys -> [x:ys]++[ys]) (f' xs)

g :: [a] -> [ (a, [a]) ]
g [] = mzero
g (x:xs) =
	return (x,xs) `mplus` do
		(y,ys) <- g xs
		return (y,x:ys)

g' :: [a] -> [ (a, [a]) ]
g' [] = []
g' (x:xs) = [(x,xs)] ++ ( concatMap (\(y,ys) -> [(y,x:ys)]) (g' xs) )

h :: [a] -> [[a]]
h [] = return []
h xs = do
	(y,ys) <- g xs
	zs <- h ys
	return (y:zs)

h' [] = [[]]
h' xs = concatMap (\ (y,ys) -> concatMap (\ zs -> [(y:zs)]) (h' ys)) (g' xs)








