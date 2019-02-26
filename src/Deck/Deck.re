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
       ) => {
  type t =
    | Nigiri1(Nigiri1.t)
    | Nigiri2(Nigiri2.t)
    | Nigiri3(Nigiri3.t)
    | Special1(Special1.t);

  type full_deck = unit;

  let getNewSortedDeck = () =>
    [
      Nigiri1.getNewSortedDeck() |> ListLabels.map(~f=t => Nigiri1(t)),
      Nigiri2.getNewSortedDeck() |> ListLabels.map(~f=t => Nigiri2(t)),
      Nigiri3.getNewSortedDeck() |> ListLabels.map(~f=t => Nigiri3(t)),
      Special1.getNewSortedDeck() |> ListLabels.map(~f=t => Special1(t)),
    ]
    |> List.concat;

  let score = (pCtx, gCtx, t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.score(pCtx, gCtx, n)
    | Nigiri2(n) => Nigiri2.score(pCtx, gCtx, n)
    | Nigiri3(n) => Nigiri3.score(pCtx, gCtx, n)
    | Special1(s) => Special1.score(pCtx, gCtx, s)
    };

  let updateGameContext = (gCtx, t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.updateGameContext(gCtx, n)
    | Nigiri2(n) => Nigiri2.updateGameContext(gCtx, n)
    | Nigiri3(n) => Nigiri3.updateGameContext(gCtx, n)
    | Special1(s) => Special1.updateGameContext(gCtx, s)
    };

  let updatePlayerContext = (pCtx, t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.updatePlayerContext(pCtx, n)
    | Nigiri2(n) => Nigiri2.updatePlayerContext(pCtx, n)
    | Nigiri3(n) => Nigiri3.updatePlayerContext(pCtx, n)
    | Special1(s) => Special1.updatePlayerContext(pCtx, s)
    };

  let getImage = (t: t) =>
    switch (t) {
    | Nigiri1(n) => Nigiri1.getImage(n)
    | Nigiri2(n) => Nigiri2.getImage(n)
    | Nigiri3(n) => Nigiri3.getImage(n)
    | Special1(s) => Special1.getImage(s)
    };

  let toString = (t: t) =>
    switch (t) {
    | Nigiri1(n) => "(Nigiri1 " ++ Nigiri1.toString(n) ++ ")"
    | Nigiri2(n) => "(Nigiri2 " ++ Nigiri2.toString(n) ++ ")"
    | Nigiri3(n) => "(Nigiri3 " ++ Nigiri3.toString(n) ++ ")"
    | Special1(s) => "(Special1 " ++ Special1.toString(s) ++ ")"
    };
};
