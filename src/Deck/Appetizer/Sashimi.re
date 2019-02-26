type t = unit; // int shows how many makis it contains

type appetizer = unit;

let getNewSortedDeck = () => Utils.repeat(10, ~f=_i => ());

let score = (ctx, _ctx, _t) => PlayerScoringCtx.shouldScoreSashimi(ctx) ? 10 : 0;

let getTallyCtx = (_pCtx, eCtx) => eCtx;

let tally = (_pCtx, _eCtx) => 0;

let updateGameContext = (ctx, _t) => ctx;

let updatePlayerContext = (ctx, _t) => PlayerScoringCtx.addSashimiCount(ctx);

let getImage = _t => Constants.imgBase ++ "sashimi.png";

let toString = _t => "(Sashimi)";
