
newtype Cyc a b = Cyc (Cyclist a -> (b, Cyclist a)) 

instance Monad (Cyc a) where 
    (Cyc comp) >>= f = 
        Cyc (\st -> 
            let (x, st') = comp st 
                Cyc comp' = f x                                  
            in comp' st') 
    return x = Cyc (\st -> (x, st)) 


runCyc :: Cyclist a -> (Cyc a b) -> b 
runCyc st (Cyc comp) = fst $ comp st 

fwd :: Cyc a () 
fwd = Cyc (\st -> ((), forward st)) 

bkw :: Cyc a () 
bkw = Cyc (\st -> ((), backward st))

lbl :: Cyc a a
lbl = Cyc (\st -> (label st, st)) 
