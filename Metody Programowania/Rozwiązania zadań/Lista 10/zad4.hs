import Data.List

msortn :: Ord a => [a] -> Int -> [a]
msortn xs 0 = [] 
msortn x:xs 1 = [x]
msortn xs n = merge (msortn xs k) (msortn (drop k xs) (n-k))
