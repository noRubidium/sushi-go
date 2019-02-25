module type S = {
    type t;

    type card;

    let newGame: (list(card)) => t;

    let getHand: t => list(card);

    let getTable: t => list(card);

    let select: (t, card) => t;

    let getSelected: t => option(card);

    let play: t => t;

    let nextRound: (t, ~newHand: list(card)) => t;

    let isHandEmpty: t => bool;

    let toString: t => string;
};

module Make = (Deck: Deck.S) => {
    type card = Deck.t;

    type t = {
        hand: list(card),
        table: list(card),
        nextHand: list(card),
        nextTable: list(card),
        selectedCard: option(card),
    };
    
    let newGame = (hand) => { hand, table: [], selectedCard: None, nextHand: hand, nextTable: [] };
    
    let getHand = t => t.hand;
    
    let getTable = t => t.table;
    
    let findOneToPlay = (list: list('a), v: 'a) =>
        ListLabels.fold_right(~init=(None, []), ~f=(elem, acc) => switch (acc) {
            | (None, l) => if (elem === v) (Some(elem), l) else (None, [elem, ...l])
            | (Some(v), l) => (Some(v), [elem, ...l])
            }
        , list)
    ;
    
    let mePlay = ({ hand, table }, card) => {
        let (card, hand) = findOneToPlay(hand, card);
        switch card {
        | None => None
        | Some(card) => Some((hand, [card, ...table]))
        };
    };
    
    let select = (t, card) => {
        switch (mePlay(t, card)) {
        | None => t;
        | Some((nextHand, nextTable)) => { ...t, selectedCard: Some(card), nextHand, nextTable };
        };
    };

    let getSelected = t => t.selectedCard;

    let play = ({ nextHand, nextTable }) => { hand: nextHand, table: nextTable, nextHand, nextTable, selectedCard: None };

    let nextRound = (t, ~newHand) => { ...t, hand: newHand, nextHand: newHand, selectedCard: None };
    
    let isHandEmpty = t => t.hand === [];
    
    let toString = t => "(Player (Hand(" ++ Utils.string_of_list(t.hand, ~f=Deck.toString) ++ 
        "), Table(" ++ Utils.string_of_list(t.table, ~f=Deck.toString)++ ")))";
}
