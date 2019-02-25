// This is the context that's used when scoring the cards.
type t = {
    misoSoupPlayed: bool,
};

// Gamewise context usually lives on for one round
let newCtx = () => { misoSoupPlayed: false };
