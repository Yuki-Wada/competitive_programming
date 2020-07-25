let () = Scanf.scanf "%d\n" @@ fun n ->
    let as_ = Array.init n @@ fun _ -> Scanf.scanf "%d " @@ fun a -> a in
    let q = Scanf.scanf "%d\n" @@ fun n -> n in
    let bcs_ = Array.init q @@ fun _ -> Scanf.scanf "%d %d\n" @@ fun b c -> (b, c) in
    let sum = Array.fold_left (+) 0 as_ in
    let max_num = 100001 in
    let counts = Array.make (max_num + 1) 0 in
    ignore @@ Array.map (fun a -> Array.set counts a @@ (+) 1 @@ Array.get counts a) @@ as_;
    let calc_diff (b, c) =
        let count_b = Array.get counts b in
        ignore @@ Array.set counts b 0;
        ignore @@ Array.set counts c @@ (+) count_b @@ Array.get counts c;
        count_b * (c - b)
    in
    let accum values value = match values with
        [] -> [value]
        | values -> (value + List.hd values) :: values
    in
    let diffs = Array.map calc_diff @@ bcs_ in
    let accum_diffs = Array.of_list @@ List.rev @@ Array.fold_left accum [] diffs in
    ignore @@ Array.map (fun diff -> Printf.printf "%d\n" @@ (+) diff sum) @@ accum_diffs
