perm [] = [[]]
perm (x:xs) = concatMap (insert x) (perm xs)

insert x [] = [[x]]
insert x ys@(y:ys') = [x:ys]++(map (y:) (insert x ys'))