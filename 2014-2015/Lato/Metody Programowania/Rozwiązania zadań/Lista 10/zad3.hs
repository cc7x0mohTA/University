import Data.List

merge_unique ::Ord a => [a] -> [a] -> [a]
merge_unique [] ys = ys
merge_unique xs [] = xs
merge_unique (x:xs) (y:ys)
    |x==y = merge_unique xs (y:ys)
    |x<y = x:(merge_unique xs (y:ys))
    |otherwise = y:(merge_unique (x:xs) ys)


d235 :: [Integer]
d235 = 1:(merge_unique (merge_unique (map (2*) d235) (map (3*) d235)) (map (5*) d235))
