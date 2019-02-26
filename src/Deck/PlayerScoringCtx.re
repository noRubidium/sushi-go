// This is the context that's used when scoring the cards.
type t = {
  tripleScoringNigiri: int,
  randomField: int,
};

let newCtx = () => {tripleScoringNigiri: 0, randomField: 0};

let addTripleScoringNigiri = (t: t) => {
  ...t,
  tripleScoringNigiri: t.tripleScoringNigiri + 1,
};

let removeTripleScoringNigiri = (t: t) => {
  ...t,
  tripleScoringNigiri: t.tripleScoringNigiri - 1,
};

let hasTripleScoringNigiri = (t: t) => t.tripleScoringNigiri != 0;
