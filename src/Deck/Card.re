module type S = {
  type t;

  let getNewSortedDeck: unit => list(t);

  let score: (PlayerScoringCtx.t, GameScoringCtx.t, t) => int;

  let updateGameContext: (GameScoringCtx.t, t) => GameScoringCtx.t;

  let updatePlayerContext: (PlayerScoringCtx.t, t) => PlayerScoringCtx.t;

  let getImage: t => string;

  let toString: t => string;
};
