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

    let calculatePoints = (l) => List.length(l) * N.num_points;

    let getImage = (_t) => N.image;

    let toString = (_t) => "(" ++ N.name ++ ")";

}
