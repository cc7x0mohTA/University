import Data.List
halve:: [a] -> ([a],[a])
halve xs = ((take k xs),( drop k xs))
    where k = ((length xs) `div` 2)

merge:: Ord a => ([a],[a]) -> [a]
merge (xs,[]) = xs
merge ([],ys) = ys
merge(x:xs,y:ys) = if x<=y then x:merge(xs,y:ys) else y:merge(x:xs,ys)

cross :: (a -> c, b -> d) -> (a,b) -> (c,d)
cross (f,g) = pair (f . fst, g . snd)
pair :: (a-> b, a -> c) -> a -> (b,c)
pair (f,g) x = (f x, g x)
msort [] = []
msort [x] = [x]
msort xs = merge . cross (msort,msort) . halve $ xs
