module type S = {
  type t;

  let getNewSortedDeck: unit => list(t);

  let score: (PlayerScoringCtx.t, GameScoringCtx.t, t) => int;

  let updateGameContext: (GameScoringCtx.t, t) => GameScoringCtx.t;

  let updatePlayerContext: (PlayerScoringCtx.t, t) => PlayerScoringCtx.t;

  let getTallyCtx: (PlayerScoringCtx.t, EndOfGameCtx.t) => EndOfGameCtx.t;

  let tally: (PlayerScoringCtx.t, EndOfGameCtx.t) => int;

  let getImage: t => string;

  let toString: t => string;
};
