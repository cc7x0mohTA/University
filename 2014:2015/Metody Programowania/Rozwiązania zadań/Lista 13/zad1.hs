import Data.List
import Control.Monad

-- potrzebne by sprawdzac czy nie ma konfliktow po skosie
check f = length . nub . zipWith f [0..]

-- bez monad:
-- generate n = filter (\x -> check (+) x == n && check (-) x == n) $ permutations [0..n-1]

-- z monadami:
generate n = do
		x <- permutations [0..n-1]
		guard(check (+) x == n && check (-) x == n)
		return x
 
main = print $ generate 8
