type t = 
    | Three
    | Two
    | One; // int shows how many makis it contains

type roll = unit;

let getNewSortedDeck = () => [Three, Three, Two, Two, Two, One, One, One, One];

let score = (_ctx, _ctx, _t) => 0;

let getTallyCtx = (pCtx, eCtx) => EndOfGameCtx.addRollCount(PlayerScoringCtx.getRollCount(pCtx), eCtx);

let tally = (pCtx, eCtx) => switch(EndOfGameCtx.getRollRank(PlayerScoringCtx.getRollCount(pCtx), eCtx)) {
| 0 => 6
| 1 => 3
| _ => 0
};

let updateGameContext = (ctx, _t) => ctx;

let updatePlayerContext = (ctx, t) =>
  PlayerScoringCtx.addRollCount(ctx, switch(t) {
  | Three => 3
  | Two => 2
  | One => 1
  });

let getImage = _t => Constants.imgBase ++ "maki.png";

let toString = _t => "(Wasabi)";
