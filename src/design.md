We have 


// We have hex color, rgba and other colors as well
// Use dom for now. Upgrade to drawing in later versions
module type Color {
    type t;

    let toHTMLColor: t => string;
}

Point(C: Color) {
    type t;

    let P: (~x: int, ~y: int, ~c: C.t) => t;

    let x: t => int;

    let y: t => int;

    let color: t => C.t;
}

Canvas(C: Color) {
    type t;

    let P = Point(C);

    let drawPoint: (t, ~point: P.t) => t; // Should I return void and just mutate the canvas instead?
}

Card {
    type t;

    let points: list(t) => int;

    let draw: t => string;

    let toString: t => string;
}


module type TamagoNigiri {
    open Card;
}

module type SalmonNigiri {
    open Card;
}

module type SquidNigiri {
    open Card;
}

// Sadly there's no type safe way to ensure we have three unique entrees
module type Entree {
    open Card;

    let entreeFlag: boolean; // Use this to prevent module casting lol
}

module type MisoSoup {
    open Entree;
}

Deck(N: TamagoNigiri, N: SalmonNigiri, N: SquidNigiri, E1: Entree, E2: Entree, E3: Entree, R: Roll, S1: Special, S2: Special, D: Dessert) {
    type t;

    let getNextCard: t => Card.t;
}

Game(Deck: Deck) {
    type t; // Should contain all the players

    let newGame: (~numPlayer: int, ~numHand: int) => t;

    let nextRound: t => void;

    let playCard: (t, Player.t, Card.t) => t;

    let getError: t => option(string);
}

Player {
    type t;

    let showHand: t => list(Card.t);

    let showTable: t => list(Card.t);

    let playCard: (t, Card.t) => or_error(t); // Returns `an error` if the card is not in the hand. How can I make this more elegant? Passing index will be messy as well. 
}
