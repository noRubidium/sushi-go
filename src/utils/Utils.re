let repeat = (n, ~f) => {
    let rec repeat = (n, ~acc, ~f) => 
    if (n > 0) {
        repeat(n - 1, ~acc=[f(n),...acc], ~f)
    } else {
        acc
    };
    repeat(n, ~f, ~acc=[]);
};

let rec hex_of_int = (i: int) => 
if (i < 10) {
    string_of_int(i);
} else {
    switch (i) {
    | 10 => "A"
    | 11 => "B"
    | 12 => "C"
    | 13 => "D"
    | 14 => "E"
    | 15 => "F"
    | _  => hex_of_int(i / 16) ++ hex_of_int(i mod 16)
    }
};

let rec pad_to_n = (s, ~n, ~pad) => if (String.length(s) < n) {
    pad_to_n(pad ++ s, ~n, ~pad);
} else {
    s
};

let get_all = (l: list(option('a))) => ListLabels.fold_left(~f=(l, e) => switch(e) {
| Some(e) => [e, ...l]
| None => l
}, ~init=[], l);

let shuffle = (l: list('a)) => 
    List.map(c => (Random.bits (), c), l)
    |> ListLabels.sort(~cmp=((a1, _b1), (a2, _b2)) => a1 - a2)
    |> List.map(snd);

let splice = (l: list('a), ~n: int) => {
    let rec splice = (l: list('a), ~n: int, ~acc) => 
        if (n <= 0) {
            (acc, l);
        } else {
            switch l {
            | [] => (acc, l)
            | [hd, ...tl] => splice(tl, ~n=(n - 1), ~acc=[hd, ...acc])
            };
        }
    splice(l, ~n, ~acc=[])
}

let string_of_list = (l, ~f) => ListLabels.fold_left(~f=(s, e) => s ++ "(" ++ f(e) ++ ")", ~init="(", l) ++ ")";
