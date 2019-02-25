module type S = {
    include Card.S;
    type full_deck;
};

module Make = (Nigiri1: Nigiri.S, Nigiri2: Nigiri.S, Nigiri3: Nigiri.S) => {
    type t = 
    | Nigiri1(Nigiri1.t)
    | Nigiri2(Nigiri2.t)
    | Nigiri3(Nigiri3.t)
    ;

    type full_deck = unit;

    let getNewSortedDeck = () =>
    [(Nigiri1.getNewSortedDeck()
    |> ListLabels.map(~f=t => Nigiri1(t))), 
    (Nigiri2.getNewSortedDeck()
    |> ListLabels.map(~f=t => Nigiri2(t))), 
    (Nigiri3.getNewSortedDeck()
    |> ListLabels.map(~f=t => Nigiri3(t))), 
    ]
    |> List.concat;

    let score = (t, pCtx, gCtx) => switch(t) {
    | Nigiri1(n) => Nigiri1.score(n, pCtx, gCtx)
    | Nigiri2(n) => Nigiri2.score(n, pCtx, gCtx)
    | Nigiri3(n) => Nigiri3.score(n, pCtx, gCtx)
    };

    let updateGameContext = (t, gCtx) => switch(t) {
    | Nigiri1(n) => Nigiri1.updateGameContext(n, gCtx)
    | Nigiri2(n) => Nigiri2.updateGameContext(n, gCtx)
    | Nigiri3(n) => Nigiri3.updateGameContext(n, gCtx)
    };

    
    let updatePlayerContext = (t, pCtx) => switch(t) {
    | Nigiri1(n) => Nigiri1.updatePlayerContext(n, pCtx)
    | Nigiri2(n) => Nigiri2.updatePlayerContext(n, pCtx)
    | Nigiri3(n) => Nigiri3.updatePlayerContext(n, pCtx)
    };        

    let getImage = (t: t) => 
    switch(t) {
    | Nigiri1(n) => Nigiri1.getImage(n)
    | Nigiri2(n) => Nigiri2.getImage(n)
    | Nigiri3(n) => Nigiri3.getImage(n)
    };

    let toString = (t: t) => 
    switch(t) {
    | Nigiri1(n) => "(Nigiri1 " ++ Nigiri1.toString(n) ++ ")"
    | Nigiri2(n) => "(Nigiri2 " ++ Nigiri2.toString(n) ++ ")"
    | Nigiri3(n) => "(Nigiri3 " ++ Nigiri3.toString(n) ++ ")"
    };
}
