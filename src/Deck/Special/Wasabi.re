open! Utils;

type t = unit;

type special = unit;

let getNewSortedDeck = () => List.repeat(3, ~f=_i => ());

let score = (_ctx, _ctx, _t) => 0;

let getTallyCtx = (_ctx, ctx) => ctx;

let tally = (_ctx, _ctx) => 0;

let updateGameContext = (ctx, _t) => ctx;

let updatePlayerContext = (ctx, _t) =>
  PlayerScoringCtx.addTripleScoringNigiri(ctx);

let getImage = _t => Constants.imgBase ++ "wasabi.png";

let toString = _t => "(Wasabi)";
