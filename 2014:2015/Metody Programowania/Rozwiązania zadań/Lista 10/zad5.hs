class Monoid a where
    (***) :: a -> a -> a
    e :: a
infixl 6 ***

infixr 7 ^^^
(^^^) :: Monoid a => a -> Int -> a
a ^^^ 0 = e
a ^^^ n
    |n<0 = undefined
    |odd n = a *** k *** k  
    |otherwise = k *** k
        where k = a ^^^ (n `div` 2)

instance Monoid Integer where
    (***) n m= (n * m) `mod` 9876543210
    e = 1

--print  $ ( 123567890 ^^^ 1234567890) `mod` 9876543210

