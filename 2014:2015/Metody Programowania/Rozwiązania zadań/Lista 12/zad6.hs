data Cyclist a = Elem (Cyclist a) a (Cyclist a)

fromList :: [a] -> Cyclist a

fromList (x:xs) = res
        where
                res = Elem prev x next
                (next, prev) = aux res xs res

aux prev [] first = (first, prev)
aux prev (x:xs) first = (this, last)
        where
                this = Elem prev x tmp
                (tmp, last) = aux this xs first

-- Ponizej : Bardzo latwe !

forward :: Cyclist a -> Cyclist a
forward ( Elem _ _ a  ) = a

backward :: Cyclist a -> Cyclist a
backward ( Elem a _ _ ) = a

label :: Cyclist a -> a
label ( Elem _ a _ ) = a

-- ---------------

enumInts :: Cyclist Integer
enumInts = Elem neg 0 pos where 
    neg = negative enumInts (-1) 
    pos = positive enumInts 1 

negative :: (Num a) => Cyclist a -> a -> Cyclist a
negative gt x = this where 
    this = Elem lt x gt
    lt = negative this (x-1) 

positive :: (Num a) => Cyclist a -> a -> Cyclist a
positive lt x = this where 
    this = Elem lt x gt 
    gt = positive this (x+1) 


ex6 :: Integer
ex6 = label . forward . forward $ enumInts

main = putStrLn $ show $ ex6
