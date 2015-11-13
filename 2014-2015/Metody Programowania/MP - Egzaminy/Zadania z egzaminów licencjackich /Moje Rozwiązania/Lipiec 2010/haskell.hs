-- Bartosz Jan Bednarczyk, 18.06.2015

-- a) Zapisane na trzy rozne sposoby - bo czemu nie :)

-- normalnie : 

allMult :: Int -> [[Int]]
allMult 0 = [[]]
allMult k = (map (1:) $  allMult(k-1)) ++ (map ((-1):) $ allMult(k-1))

-- list comp :

allMult' :: Int -> [[Int]]
allMult' 0 = [[]]
allMult' k = concat [ [(1:xs), (-1):xs] | xs <- allMult(k-1) ]

-- monadycznie :

allMult'' :: Int -> [[Int]]
allMult'' 0 = [[]]
allMult'' k = do
		xs <- allMult'' (k-1)
		x <- [-1,1]
		return $ (x:xs)

-- b)

-- z gotowymi funkcjami :

dotProduct :: [Int] -> [Int] -> Int
dotProduct xs ys = sum $ zipWith (*) xs ys

-- bez gotowych funkcji :

dotProduct' [] [] = 0
dotProduct' (x:xs) (y:ys) = x*y + dotProduct' xs ys

-- c)

good :: [Int] -> Int -> Bool
good xs k = k `elem` (gen xs)

-- gen monadycznie

gen :: [Int] -> [Int]
gen [] = [0]
gen (x:xs) = do
		a <- gen xs
		b <- [-x, x]
		return $ (a+b)

-- gen za pomoca list comp

gen' :: [Int] -> [Int]
gen' [] = [0]
gen' (x:xs) = [ a+b | a <- gen' xs, b <- [-x,x] ]

-- gen bez bajerow

gen'' :: [Int] -> [Int]
gen'' [] = [0]
gen'' (x:xs) = (map (+x) (gen''(xs)) ) ++ ( map (+(-x)) (gen''(xs)) )
