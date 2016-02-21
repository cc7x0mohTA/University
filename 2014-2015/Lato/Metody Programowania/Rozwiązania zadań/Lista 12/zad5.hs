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

--label.forward.forward.forward.backward.forward.forward $ fromList [1,2,3] = 2
