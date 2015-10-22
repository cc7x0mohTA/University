import Data.List as L

-- a)

quicksort :: Ord a => [a] -> [a]
quicksort []     = []
quicksort (p:xs) = (quicksort lesser) ++ [p] ++ (quicksort greater)
    where
        lesser  = filter (< p) xs
        greater = filter (>= p) xs

-- b)

len :: [a] -> Int
len [] = 0
len (x:xs) = 1 + len xs

len' :: [a] -> Int
len' = foldr (\ _ x -> x+1) 0

len'' :: [a] -> Int
len'' = foldl (\ x _ -> x+1) 0 

-- c)

setSize :: [Int] -> Int
setSize = length . (L.nub)
