length1 = foldr (\ _ x -> x + 1) 0 

length2 :: [a] -> Int
length2 = foldl (\ x _ -> x + 1) 00
(+++) = flip $ foldr (:)
concat = foldr (++) []
reverse = foldl (flip (:)) []
sum = foldl (+) 0