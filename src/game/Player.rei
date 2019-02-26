module Make:
  (D: Deck.S) =>
   {
    type t;

    type card = D.t;

    let newGame: (list(card), string) => t;

    let getHand: t => list(card);

    let getTable: t => list(card);

    let select: (card, t) => t;

    let getSelected: t => option(card);

    let getScore: t => int;

    let play: t => t;

    let nextRound: (t, ~newHand: list(card)) => t;

    let isHandEmpty: t => bool;

    let toString: t => string;
    let getId: t => string;

    module Scoring: {
      let updateGameCtx: (t, GameScoringCtx.t) => GameScoringCtx.t;

      let updatePlayerCtx: t => t;

      let scoreThisTurn: (t, GameScoringCtx.t) => t;

      let updateEndOfGameCtx: (t, EndOfGameCtx.t) => EndOfGameCtx.t;

      let tally: (EndOfGameCtx.t, t) => t;
    };
  };
