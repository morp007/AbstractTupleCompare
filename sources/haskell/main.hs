l45_abstractCompare' [] [] = EQ
l45_abstractCompare' _ [] = GT
l45_abstractCompare' [] _ = LT
l45_abstractCompare' (rx:rxs) (ry:rys) | compareRes == EQ = rxs `l45_abstractCompare'` rys
                                       | otherwise = compareRes
                                       where
                                           compareRes = rx `compare` ry
l45_abstractCompare :: Ord a => [a] -> [a] -> Ordering
l45_abstractCompare x y = reverse x `l45_abstractCompare'` reverse y


main = do
    print $ l45_abstractCompare [1..100000000] [1..100000000]
