// This is the context that's used when scoring the cards.
type t = {
  tripleScoringNigiri: int,
  rollCount: int, // Used to count how many rolls there are
  randomField: int,
  sashimiCount: int,
};

let newCtx = () => {tripleScoringNigiri: 0, randomField: 0, rollCount: 0, sashimiCount: 0};

let addTripleScoringNigiri = (t: t) => {
  ...t,
  tripleScoringNigiri: t.tripleScoringNigiri + 1,
};

let removeTripleScoringNigiri = (t: t) => {
  ...t,
  tripleScoringNigiri: t.tripleScoringNigiri - 1,
};

let hasTripleScoringNigiri = (t: t) => t.tripleScoringNigiri != 0;

let addRollCount = (t, n) => {
    ...t,
    rollCount: t.rollCount + n,
};

let getRollCount = t => t.rollCount;

let addSashimiCount = t => {
  ...t,
  sashimiCount: 1 + t.sashimiCount,
};

let shouldScoreSashimi = t => t.sashimiCount mod 3 === 2;
