let () = Scanf.scanf "%d\n" @@ fun n ->
    if n == 1 then Printf.printf "%d\n" 0 else
    let sqrtn = (int_of_float @@ sqrt @@ float_of_int n) + 1
    in let is_primes = Array.init (sqrtn + 1) @@ fun n -> (n, true)
    in let sieve (i, is_prime) =
        if i >= 2 && is_prime
        then
            let rec multiple_to_false j =
                if i * j <= sqrtn then (
                    Array.set is_primes (i * j) (i * j, false);
                    multiple_to_false @@ j + 1
                )
            in multiple_to_false 2
    in ignore @@ Array.map sieve is_primes;
    let rec get_exp e n p =
        if (n mod p) == 0 then get_exp (e + 1) (n / p) p else e
    in let rec get_pow p e =
        if e == 0 then 1 else p * (get_pow p @@ e - 1)
    in let rec get_res n p =
        let e = get_exp 0 n p
        in let rec get_val i =
            if (i + 1) * (i + 2) / 2 <= e then get_val (i + 1)
            else i
        in get_val 0
    in let quot = Array.fold_left
        (fun x y -> x / y) n @@
        Array.map (fun (i, is_prime) -> if i >= 2 && is_prime then get_pow i (get_exp 0 n i) else 1) is_primes
    in Printf.printf "%d\n" @@ Array.fold_left (+) (if quot > 1 then 1 else 0) @@
        Array.map (fun (i, is_prime) -> if i >= 2 && is_prime then get_res n i else 0) is_primes
    
