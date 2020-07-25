let rec upper_bound l r p =
    if r <= 1 + l
    then l
    else let m = (l + r) / 2 in
        if p m 
        then upper_bound m r p
        else upper_bound l m p

let () = Scanf.scanf "%d %d %d\n" @@ fun n m k ->
    let as_ = Array.init n @@ fun _ -> Scanf.scanf "%d " @@ fun a -> a in
    let bs = Array.init m @@ fun _ -> Scanf.scanf "%d " @@ fun b -> b in
    let accum values value = match values with
        [] -> [value]
        | values -> (value + List.hd values) :: values in
    let inc = Array.of_list @@ List.rev @@ Array.fold_left accum [0] as_ in
    let inc' =  Array.of_list @@ List.rev @@ Array.fold_left accum [0] bs in
    Printf.printf "%d\n" @@
    Array.fold_left max min_int @@
    Array.init (n + 1) @@ fun i ->
        if k < inc.(i) then 0
        else i + upper_bound 0 (m + 1) (fun j -> inc.(i) + inc'.(j) <= k)
