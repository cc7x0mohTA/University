sublist :: [a] -> [[a]]
sublist [] = [[]]
sublist (x:xs) = concatMap (\ys -> [x:ys, ys]) $ sublist xs

sublist2 :: [a] -> [[a]]
sublist2 [] = [[]]
sublist2 (x:xs) = [res | ys <- sublist2 xs, res <- [x:ys, ys]]


sublist3 :: [a] -> [[a]]
sublist3 [] = [[]]
sublist3 (x:xs) = do
        ys <- sublist3 xs
        res <- [x:ys, ys]
        return res