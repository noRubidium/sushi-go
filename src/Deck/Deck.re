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

    let calculatePoints = (cards: list(t)) => {
        let n1_points = (cards 
        |> ListLabels.map(~f=t => switch t {
        | Nigiri1(n) => Some(n)
        | _ => None
        })
        |> Utils.get_all
        |> Nigiri1.calculatePoints);
        let n2_points = (cards 
        |> ListLabels.map(~f=t => switch t {
        | Nigiri2(n) => Some(n)
        | _ => None
        })
        |> Utils.get_all
        |> Nigiri2.calculatePoints);
        let n3_points = (cards 
        |> ListLabels.map(~f=t => switch t {
        | Nigiri3(n) => Some(n)
        | _ => None
        })
        |> Utils.get_all
        |> Nigiri3.calculatePoints);
        n1_points + n2_points + n3_points;
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
