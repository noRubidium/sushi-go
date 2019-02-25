module type S = {
    type t;

    type card;

    let newGame: (list(card), string) => t;

    let getHand: t => list(card);

    let getTable: t => list(card);

    let select: (card, t) => t;

    let getSelected: t => option(card);

    let play: t => t;

    let nextRound: (t, ~newHand: list(card)) => t;

    let isHandEmpty: t => bool;

    let toString: t => string;
    let getId: t => string;
    
    module Scoring: {
        let updateGameCtx: (t, GameScoringCtx.t) => GameScoringCtx.t;

        let updatePlayerCtx: t => PlayerScoringCtx.t;

        let scoreThisTurn: (t, GameScoringCtx.t) => int;
    }
};

module Make: (D: Deck.S) => {
    include S with type card := D.t;
};
