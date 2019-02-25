module Make: (D: Deck.S) => {
    type t;
    
    type table = { id: string, cards: list(D.t)};

    let newGame: (~numCards: int, ~numPlayers: int) => t;
    
    let getTable: t => list(table);

    let getHand: t => list(D.t);

    let getCurrentPlayerId: t => string;
    
    let select: (t, D.t) => t;

    let play: t => t;

    let nextPlayer: t => t;

    let hasSelectedCard: t => bool;

    let showSelectedCard: t => option(D.t);
    
    let nextRound: t => t;
    
    let isGameEnd: t => bool;
    
    let toString: t => string;
};
