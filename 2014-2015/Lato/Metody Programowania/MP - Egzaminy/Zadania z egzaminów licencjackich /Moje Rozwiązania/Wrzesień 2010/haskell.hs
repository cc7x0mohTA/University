
-- a) szybki reverse

rev1 :: [a] -> [a]
rev1 xs = foldl (flip (:)) [] xs

-- b) reverse z definicji

rev2 :: [a] -> [a]
rev2 [] = []
rev2 (x:xs) = rev2 xs ++ [x]

-- c) listToNumber

listToNumber :: [Int] -> Int
listToNumber = foldl (\ x -> \y -> 10*x + y) 0

-- d) numberToList

numberToList = reverse.unfoldr
		(\x -> if x == 0 then Nothing else Just (mod x 10, div x 10))
