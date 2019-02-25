module type S = {
    type t;

    type card;

    let newGame: (list(card)) => t;

    let getHand: t => list(card);

    let getTable: t => list(card);

    let play: (t, card) => option(t);

    let nextRound: (t, ~newHand: list(card)) => t;

    let isHandEmpty: t => bool;

    let toString: t => string;
};

module Make = (Deck: Deck.S) => {
    type card = Deck.t;

    type cards = (list(card), list(card));
    type t = Me(cards);
    
    let newGame = (cards) => Me((cards, []));
    
    let getHand = (t) => switch t {
        | Me((l, _)) => l
    };
    
    let getTable = (t) => switch t {
        | Me((_hand, table)) => table
    };
    
    let findOneToPlay = (list: list('a), v: 'a) =>
        ListLabels.fold_right(~init=(None, []), ~f=(elem, acc) => switch (acc) {
            | (None, l) => if (elem === v) (Some(elem), l) else (None, [elem, ...l])
            | (Some(v), l) => (Some(v), [elem, ...l])
            }
        , list)
    ;
    
    let mePlay = ((hand, table)) => card => {
        let (card, hand) = findOneToPlay(hand, card);
        switch card {
        | None => None
        | Some(card) => Some((hand, [card, ...table]))
        };
    };
    
    let play = (t, card) => {
        switch t {
        | Me(cards) => 
            switch (mePlay(cards, card)) {
            | None => None;
            | Some(l) => Some(Me(l));
            };
        };
    };
    
    let nextRound = (t: t, ~newHand: list(card)) => {
        switch t {
        | Me((_hand, table)) => Me((newHand, table))
        };
    };
    
    let isHandEmpty = t => switch t {
    | Me((hand, _)) => hand === [];
    };
    
    let toString = t => switch t {
    | Me((hand, table)) => 
        "Me: (Hand(" ++ Utils.string_of_list(hand, ~f=Deck.toString) ++ 
        "), Table(" ++ Utils.string_of_list(table, ~f=Deck.toString)++ "))"
    };
}
