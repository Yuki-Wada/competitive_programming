let comp x y = 
    if x > y then 1 else if x < y then -1 else 0

let () = Scanf.scanf "%d\n" @@ fun n ->
    let as_ = Array.make n 0 in
    let bs_ = Array.make n 0 in
    let substitute i = 
        Scanf.scanf "%d %d\n" @@ fun a b ->
            Array.set as_ i a;
            Array.set bs_ i b;
    in
    ignore @@ Array.map substitute @@ (Array.init n @@ fun u -> u);
    ignore @@ Array.sort comp as_;
    ignore @@ Array.sort comp bs_;
    let res = 
        if n mod 2 == 0
        then
            (Array.get bs_ @@ n / 2) + (Array.get bs_ @@ n / 2 - 1)
            - (Array.get as_ @@ n / 2) - (Array.get as_ @@ n / 2 - 1) + 1
        else
            (Array.get bs_ @@ n / 2) - (Array.get as_ @@ n / 2) + 1
    in
    ignore @@ Printf.printf "%d\n" @@ res
