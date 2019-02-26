module type S = {
  include Card.S;
  type full_deck;
};

module Make =
       (
         Nigiri1: Nigiri.S,
         Nigiri2: Nigiri.S,
         Nigiri3: Nigiri.S,
         Special1: Special.S,
         Special2: Special.S,
         Roll: Roll.S,
       ) => {
  type t =
    | Nigiri1(Nigiri1.t)
    | Nigiri2(Nigiri2.t)
    | Nigiri3(Nigiri3.t)
    | Special1(Special1.t)
    | Special2(Special2.t)
    | Roll(Roll.t);

  type full_deck = unit;

  let getNewSortedDeck = () =>
    [
      Nigiri1.getNewSortedDeck() |> ListLabels.map(~f=t => Nigiri1(t)),
      Nigiri2.getNewSortedDeck() |> ListLabels.map(~f=t => Nigiri2(t)),
      Nigiri3.getNewSortedDeck() |> ListLabels.map(~f=t => Nigiri3(t)),
      Special1.getNewSortedDeck() |> ListLabels.map(~f=t => Special1(t)),
      Special2.getNewSortedDeck() |> ListLabels.map(~f=t => Special2(t)),
      Roll.getNewSortedDeck() |> ListLabels.map(~f=t => Roll(t)),
    ]
    |> List.concat;

  let score = (pCtx, gCtx, t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.score(pCtx, gCtx, n)
    | Nigiri2(n) => Nigiri2.score(pCtx, gCtx, n)
    | Nigiri3(n) => Nigiri3.score(pCtx, gCtx, n)
    | Special1(s) => Special1.score(pCtx, gCtx, s)
    | Special2(s) => Special2.score(pCtx, gCtx, s)
    | Roll(s) => Roll.score(pCtx, gCtx, s)
    };

  let updateGameContext = (gCtx, t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.updateGameContext(gCtx, n)
    | Nigiri2(n) => Nigiri2.updateGameContext(gCtx, n)
    | Nigiri3(n) => Nigiri3.updateGameContext(gCtx, n)
    | Special1(s) => Special1.updateGameContext(gCtx, s)
    | Special2(s) => Special2.updateGameContext(gCtx, s)
    | Roll(s) => Roll.updateGameContext(gCtx, s)
    };

  let updatePlayerContext = (pCtx, t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.updatePlayerContext(pCtx, n)
    | Nigiri2(n) => Nigiri2.updatePlayerContext(pCtx, n)
    | Nigiri3(n) => Nigiri3.updatePlayerContext(pCtx, n)
    | Special1(s) => Special1.updatePlayerContext(pCtx, s)
    | Special2(s) => Special2.updatePlayerContext(pCtx, s)
    | Roll(s) => Roll.updatePlayerContext(pCtx, s)
    };

  let getImage = t =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.getImage(n)
    | Nigiri2(n) => Nigiri2.getImage(n)
    | Nigiri3(n) => Nigiri3.getImage(n)
    | Special1(s) => Special1.getImage(s)
    | Special2(s) => Special2.getImage(s)
    | Roll(s) => Roll.getImage(s)
    };

  let getTallyCtx = (p, g) => 
  Nigiri1.getTallyCtx(p, g)
  |> Nigiri2.getTallyCtx(p)
  |> Nigiri3.getTallyCtx(p)
  |> Special1.getTallyCtx(p)
  |> Special2.getTallyCtx(p)
  |> Roll.getTallyCtx(p);

  let tally = (p, g) =>
    Nigiri1.tally(p, g)
    + Nigiri2.tally(p, g)
    + Nigiri3.tally(p, g)
    + Special1.tally(p, g)
    + Special2.tally(p, g)
    + Roll.tally(p, g);

  let toString = t =>
    switch (t) {
    | Nigiri1(n) => "(Nigiri1 " ++ Nigiri1.toString(n) ++ ")"
    | Nigiri2(n) => "(Nigiri2 " ++ Nigiri2.toString(n) ++ ")"
    | Nigiri3(n) => "(Nigiri3 " ++ Nigiri3.toString(n) ++ ")"
    | Special1(s) => "(Special1 " ++ Special1.toString(s) ++ ")"
    | Special2(s) => "(Special2 " ++ Special2.toString(s) ++ ")"
    | Roll(s) => "(Roll " ++ Roll.toString(s) ++ ")"
    };
};
