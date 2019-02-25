module type S = {
    include Card.S;
    type nigiri;
};

module type N = {
    let num_points: int;
    let num_cards: int;
    let image: string;
    let name: string;
}

module Make = (N: N) => {
    type t = unit;

    type nigiri = unit;

    let getNewSortedDeck = () => Utils.repeat(N.num_cards, ~f=(_i) => ());

    let score = (_t, ctx, _ctx) => N.num_points * (PlayerScoringCtx.getTripleScoringNigiri(ctx) ? 3 : 1);

    let updateGameContext = (_t, ctx) => ctx;

    let updatePlayerContext = (_t, ctx) => PlayerScoringCtx.setTripleScoringNigiri(ctx, false);

    let getImage = (_t) => Constants.imgBase ++ N.image ++ ".png";

    let toString = (_t) => "(" ++ N.name ++ ")";

}
