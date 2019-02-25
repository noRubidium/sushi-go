module type S = {
    type t;

    let getNewSortedDeck: unit => list(t);

    let score: (t, PlayerScoringCtx.t, GameScoringCtx.t) => int;

    let updateGameContext: (t, GameScoringCtx.t) => GameScoringCtx.t;

    let updatePlayerContext: (t, PlayerScoringCtx.t) => PlayerScoringCtx.t;

    let getImage: t => string;

    let toString: t => string;
};
