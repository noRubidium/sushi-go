// This is the context that's used when scoring the cards.
type t = {
  tripleScoringNigiri: bool,
  randomField: int,
};

let newCtx = () => {tripleScoringNigiri: false, randomField: 0};

let setTripleScoringNigiri = (t: t, tripleScoringNigiri) => {
  ...t,
  tripleScoringNigiri,
};

let getTripleScoringNigiri = (t: t) => t.tripleScoringNigiri;
