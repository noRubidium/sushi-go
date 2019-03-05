module type S = {
  type t;
  type deck;

  type table = {
    id: string,
    cards: list(deck),
    score: int,
  };

  let newGame: (~numCards: int, ~numPlayers: int) => t;

  let getTable: t => list(table);

  let getHand: t => list(deck);

  let getCurrentPlayerId: t => string;

  let select: (t, deck) => t;

  let play: t => t;

  let nextPlayer: t => t;

  let hasSelectedCard: t => bool;

  let showSelectedCard: t => option(deck);

  let nextRound: t => t;

  let calcThisRoundPoint: t => t;

  let isRoundEnd: t => bool;

  let isGameEnd: t => bool;

  let tallyGameEnd: t => t;

  let toString: t => string;
};

module Make: (D: Deck.S) => S with type deck := D.t;
