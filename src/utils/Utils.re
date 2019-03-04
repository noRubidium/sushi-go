let hex_of_int = (i: int) => {
  let rec hex_of_int = (i: int, ~acc: string) => {
    if (i < 10) {
      string_of_int(i) ++ acc;
    } else {
      switch (i) {
      | 10 => "A" ++ acc
      | 11 => "B" ++ acc
      | 12 => "C" ++ acc
      | 13 => "D" ++ acc
      | 14 => "E" ++ acc
      | 15 => "F" ++ acc
      | _ => hex_of_int(i / 16, ~acc=acc ++ hex_of_int(i mod 16, ~acc=""));
      };
    };

  }
  hex_of_int(i, ~acc="");
};

let rec pad_to_n = (s, ~n, ~pad) =>
  if (String.length(s) < n) {
    pad_to_n(pad ++ s, ~n, ~pad);
  } else {
    s;
  };

module MyList: {
  let length: list('a) => int;
  let nth: (list('a), int) => 'a;
  let map: ('a => 'b, list('a)) => list('b);
  let fold_left: (('a, 'b) => 'a, 'a, list('b)) => 'a;
  let fold_right: (('a, 'b) => 'b, list('a), 'b) => 'b;
  let combine: (list('a), list('b)) => list(('a, 'b));

  // Custom functions
  let repeat: (int, ~f: int => 'a) => list('a);
  let shuffle: list('a) => list('a);
  let splice: (list('a), ~n: int) => (list('a), list('a));
  let updateNth: (list('a), ~n: int, ~e: 'a) => list('a);
  let rotate: list('a) => list('a);
  let getAll: list(option('a)) => list('a);
} = {
  include List;
  let repeat = (n, ~f) => {
    let rec repeat = (n, ~acc, ~f) =>
      if (n > 0) {
        repeat(n - 1, ~acc=[f(n), ...acc], ~f);
      } else {
        acc;
      };
    repeat(n, ~f, ~acc=[]);
  };

  let shuffle = l =>
    map(c => (Random.bits(), c), l)
    |> sort(((a1, _b1), (a2, _b2)) => a1 - a2)
    |> map(snd);

  let getAll = (l: list(option('a))) =>
    fold_right(
      (e, l) =>
        switch (e) {
        | Some(e) => [e, ...l]
        | None => l
        },
      l,
      [],
    );

  let splice = (l: list('a), ~n: int) => {
    let (l, r) = List.mapi((i, a) => (i, a), l) |> List.partition(((i, _a)) => i < n);
    (List.map(((_i, a)) => a, l), List.map(((_i, a)) => a, r));
  };

  let updateNth = (l, ~n, ~e) => mapi((i, v) => i === n ? e : v, l);

  let rotate = l =>
    switch (l) {
    | [] => []
    | [x, ...l] => concat([l, [x]])
    };
};
module List = MyList;

let string_of_list = (l, ~f) =>
  List.fold_left((s, e) => s ++ "(" ++ f(e) ++ ")", "(", l)
  ++ ")";
