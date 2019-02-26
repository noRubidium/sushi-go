type t = unit;

type special = unit;

let getNewSortedDeck = () => Utils.repeat(3, ~f=_i => ());

let score = (_ctx, _ctx, _t) => 0;

let updateGameContext = (ctx, _t) => ctx;

let updatePlayerContext = (ctx, _t) =>
  PlayerScoringCtx.setTripleScoringNigiri(ctx, true);

let getImage = _t => Constants.imgBase ++ "wasabi.png";

let toString = _t => "(Wasabi)";
