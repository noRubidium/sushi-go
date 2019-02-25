module Make = (D: Deck.S) => {

    module Player = Player.Make(D);

    type t = {
        currentPlayer: Player.t,
        otherPlayers: list(Player.t),
        deck: list(D.t),
    };

    let draw_n_cards = Utils.splice;

    let newGame = (~numCards: int, ~numPlayers: int) => {
        Random.self_init();
        let deck = D.getNewSortedDeck();
        let shuffled_deck = ref(Utils.shuffle(deck));
        let draw_cards = () => {
            let (hand, deck) = draw_n_cards(shuffled_deck^, ~n=numCards);
            shuffled_deck := deck;
            hand;
        };
        {
            currentPlayer: Player.newGame(draw_cards()),
            otherPlayers: Utils.repeat(numPlayers - 1, ~f=(_n) => Player.newGame(draw_cards())),
            deck: shuffled_deck^,
        }
    };

    let getTable = (t: t) => {
        (
            Player.getTable(t.currentPlayer),
            ListLabels.map(t.otherPlayers, ~f=Player.getTable)
        )
    }

    let getHand = (t: t) => Player.getHand(t.currentPlayer);

    let select = (t, card) => {
        let { currentPlayer } = t;
        { ...t, currentPlayer: Player.select(currentPlayer, card) };
    };

    let play = (t) => {
        let { currentPlayer } = t;
        { ...t, currentPlayer: Player.play(currentPlayer) };
    };

    let hasSelectedCard = t => Player.getSelected(t.currentPlayer) != None;

    let showSelectedCard = t => switch(Player.getSelected(t.currentPlayer)) {
    | Some(card) => D.toString(card)
    | None => ""
    };

    let rotateHand = (players, currentPlayerHand) => 
        ListLabels.fold_left(
            ~init=([], currentPlayerHand), 
            ~f=((players, currentHand), p) => ([Player.nextRound(p, ~newHand=currentHand), ...players], Player.getHand(p)),
            players
            )

    let nextRound = (t: t) => {
        let currentPlayerHand = Player.getHand(t.currentPlayer);
        let (otherPlayers, newHand) = rotateHand(t.otherPlayers, currentPlayerHand);
        {
            ...t,
            currentPlayer: Player.nextRound(t.currentPlayer, ~newHand),
            otherPlayers
        }
    };

    let isGameEnd = (t: t) => Player.isHandEmpty(t.currentPlayer);

    let toString = (t: t) => 
        "((CurrentPlayer(" ++ Player.toString(t.currentPlayer) ++ "))" ++
        "(OtherPlayers" ++ Utils.string_of_list(t.otherPlayers, ~f=Player.toString) ++ ")"
        ++ ")";
}

