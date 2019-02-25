module Make: (D: Deck.S) => {
    type t;
    
    let newGame: (~numCards: int, ~numPlayers: int) => t;
    
    let getTable: t => (list(D.t), list(list(D.t)));

    let getHand: t => list(D.t);
    
    let select: (t, D.t) => t;

    let play: t => t;

    let hasSelectedCard: t => bool;

    let showSelectedCard: t => string;
    
    let nextRound: t => t;
    
    let isGameEnd: t => bool;
    
    let toString: t => string;
};
