let accumulate values =
    let accum values value = match values with
        [] -> [value]
        | values -> (value + List.hd values) :: values
    in
    Array.of_list @@ List.rev @@ Array.fold_left accum [] values

let comp x y = 
    if x > y then 1 else if x < y then -1 else 0
