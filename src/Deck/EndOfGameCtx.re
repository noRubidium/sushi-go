type t = {rollCounts: list(int)};

let newCtx = () => {rollCounts: []};

let addRollCount = (e, t) => {rollCounts: [e, ...t.rollCounts]};

let getRollRank = (n, t) => List.fold_left((c, e) => e > n ? c + 1 : c, 0, t.rollCounts);
