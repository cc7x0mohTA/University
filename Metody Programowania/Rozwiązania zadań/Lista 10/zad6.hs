{-# LANGUAGE FlexibleInstances #-}

class Monoid a where
    (***) :: a -> a -> a
    e :: a
infixl 6 ***

infixr 7 ^^^
(^^^) :: Monoid a => a -> Integer -> a
a ^^^ 0 = e
a ^^^ n
    |n<0 = undefined
    |odd n = a *** k *** k  
    |otherwise = k *** k
        where k = a ^^^ (n `div` 2)

data Mtx2x2 a = Mtx2x2 a a a a deriving Show
instance Monoid (Mtx2x2 Integer) where
(***) (Mtx2x2 a11 a12 a21 a22) (Mtx2x2 b11 b12 b21 b22)= 
	Mtx2x2(a12*b21+a11*b11)(a11*b12+b22*a12)(a22*b21+a21*b11)(a21*b12+a22*b22)
    e = Mtx2x2 1 0 0 1

fib :: Integer -> Integer
fib n = let aux = (Mtx2x2 0 1 1 1)  in pole12 (aux ^^^ n)
    where pole12 (Mtx2x2 a11 a12 a21 a22) = a12

k :: (Mtx2x2 Integer)
k = Mtx2x2 0 1 1 1
