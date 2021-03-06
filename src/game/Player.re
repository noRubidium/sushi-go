module Make = (Deck: Deck.S) => {
  type card = Deck.t;

  type t = {
    hand: list(card),
    table: list(card),
    nextHand: list(card),
    nextTable: list(card),
    selectedCard: option(card),
    ctx: PlayerScoringCtx.t,
    score: int,
    id: string,
  };

  let newGame = (hand, id) => {
    hand,
    table: [],
    selectedCard: None,
    nextHand: hand,
    nextTable: [],
    ctx: PlayerScoringCtx.newCtx(),
    score: 0,
    id,
  };

  let getHand = t => t.hand;

  let getTable = t => t.table;

  let findOneToPlay = (list: list('a), v: 'a) =>
    List.fold_right(
        (elem, acc) =>
          switch (acc) {
          | (None, l) =>
            if (elem === v) {
              (Some(elem), l);
            } else {
              (None, [elem, ...l]);
            }
          | (Some(v), l) => (Some(v), [elem, ...l])
          },
      list,
      (None, []),
    );

  let mePlay = ({hand, table}, card) => {
    let (card, hand) = findOneToPlay(hand, card);
    switch (card) {
    | None => None
    | Some(card) => Some((hand, [card, ...table]))
    };
  };

  let select = (card, t) => {
    switch (mePlay(t, card)) {
    | None => t
    | Some((nextHand, nextTable)) => {
        ...t,
        selectedCard: Some(card),
        nextHand,
        nextTable,
      }
    };
  };

  let getSelected = t => t.selectedCard;

  let play = t => {
    let {nextHand, nextTable} = t;
    {...t, hand: nextHand, table: nextTable, selectedCard: None};
  };

  let getScore = t => t.score;

  let nextRound = (t, ~newHand) => {
    ...t,
    hand: newHand,
    nextHand: newHand,
    selectedCard: None,
  };

  let isHandEmpty = t => t.hand === [];

  let getId = t => t.id;

  let toString = t =>
    "(Player (Id("
    ++ getId(t)
    ++ "))(Selected"
    ++ Option.toString(t.selectedCard, ~f=Deck.toString)
    ++ ")(Hand("
    ++ Utils.string_of_list(t.hand, ~f=Deck.toString)
    ++ "), Table("
    ++ Utils.string_of_list(t.table, ~f=Deck.toString)
    ++ ")))";

  module Scoring = {
    let lastPlayed = t => List.hd(t.table);
    let updateGameCtx = (t, ctx) =>
      t |> lastPlayed |> Deck.updateGameContext(ctx);
    let updatePlayerCtx = t => {
      ...t,
      ctx: t |> lastPlayed |> Deck.updatePlayerContext(t.ctx),
    };

    let scoreThisTurn = (t: t, gCtx) => {
      let score = t |> lastPlayed |> Deck.score(t.ctx, gCtx);
      {...t, score: score + t.score};
    };

    let updateEndOfGameCtx = (t) => Deck.getTallyCtx(t.ctx);

    let tally = (eCtx, t) => {
        let score = Deck.tally(t.ctx, eCtx);
        {...t, score: score + t.score};
    }
  };
};
