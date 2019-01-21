eliminate :: Grid -> (Square, Digit) -> Maybe Grid
eliminate g (s,d) =
    let cell = lookup s g in
        if not (elem d cell) then return g
        else do let newCell = delete d cell
                    newV = M.insert s newCell g
                newV2 <- case length newCell of
                            0 -> Nothing
                            1 -> do let peersOfS = [s' | s' <- lookup s peers]
                                    res <- foldM eliminate newV (zip peersOfS (cycle newCell))
                                    return res
                            _ -> return newV
                let dPlaces = [s' | u <- lookup s units, s' <- u, elem d (lookup s' newV2)]
                case length dPlaces of
                    0 -> Nothing
                    1 -> assign newV2 (head dPlaces, d)
                    _ -> return newV2

---------------------------------------------------------------------------------------------

eliminate :: Grid -> (Square, Digit) -> Maybe Grid
eliminate g (s,d) =
    let cell = g ! s in
        if d `notElem` cell then return g
        else do let newCell = delete d cell
                    newV = g // [(s,newCell)]
                newV2 <- case newCell of
                        []   -> Nothing
                        [d'] -> do let peersOfS = peers ! s
                                   foldM eliminate newV (zip peersOfS (repeat d'))
                        _    -> return newV
                foldM (locate d) newV2 (units ! s)