module type S = {
    type t;

    let getNewSortedDeck: unit => list(t);

    let calculatePoints: list(t) => int;

    let getImage: t => string;

    let toString: t => string;
};
