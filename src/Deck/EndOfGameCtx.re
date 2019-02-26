type t = {rollCounts: list(int)};

let newCtx = () => {rollCounts: []};

let addRollCount = (e, t) => {rollCounts: [e, ...t.rollCounts]};

let getRollRank = (n, t) => ListLabels.fold_left(~f=(c, e) => e > n ? c + 1 : c, ~init=0, t.rollCounts);
