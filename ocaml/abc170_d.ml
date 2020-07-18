let () = Scanf.scanf "%d\n" @@ fun n ->
    let as_ = Array.init n @@ fun _ -> Scanf.scanf "%d " @@ fun a -> a in
    Array.sort (fun x y -> if x > y then 1 else if x < y then -1 else 0) as_;
    let max_num = 1000001 in
    let exists = Array.make (max_num + 1) 0 in
    let rec set_val m n =
        if m == 1 && (Array.get exists n) > 0 then
            if (Array.get exists n) == 2 then (
                Array.set exists n 1; -1;
            ) else 0
        else if m * n <= max_num then (
            Array.set exists (m * n) (if m > 1 then 1 else 2);
            set_val (m + 1) n;
        ) else 1 in

    Printf.printf "%d\n" @@ Array.fold_left (+) 0 @@ Array.map (set_val 1) as_ 

