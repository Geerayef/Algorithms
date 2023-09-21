(* Sort Numbers *)

(* List *)

let rec list_length (lst : 'a list) : int =
    let counter = ref 0
    in
    match lst with
    | [] -> !counter
    | _ :: [] -> counter := !counter + 1; !counter
    | _ :: t -> counter := !counter + 1; list_length t
;;

let rec sort_numbers (lst : int list) : int list = 
    let lst_length = list_length lst
    in
    let result = []
    in
    match lst with
    | [] -> []
    | h :: [] -> [h]
    | h :: t :: [] -> if h <= t then ( h :: t :: [] ) else ( t :: h :: [] )
    | h :: s :: t ->
        if h <= s then
            h :: s :: sort_numbers t
        else
            s :: h :: sort_numbers t
;;

let t = [1;2;3;4;56;6;7]
