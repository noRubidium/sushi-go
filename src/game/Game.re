module Make = (D: Deck.S) => {
  module Player = Player.Make(D);

  type t = {
    currentPlayer: int,
    players: list(Player.t),
    deck: list(D.t),
  };

  type table = {
    id: string,
    cards: list(D.t),
    score: int,
  };

  let draw_n_cards = Utils.splice;

  let nextPlayer = t => {
    ...t,
    currentPlayer: (t.currentPlayer + 1) mod List.length(t.players),
  };

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
      currentPlayer: 0,
      players:
        Utils.repeat(numPlayers, ~f=n =>
          Player.newGame(draw_cards(), string_of_int(n))
        ),
      deck: shuffled_deck^,
    };
  };

  let getCurrentPlayer = t => List.nth(t.players, t.currentPlayer);

  let setCurrentPlayer = (t, p) => {
    ...t,
    players: Utils.updateNth(t.players, ~n=t.currentPlayer, ~e=p),
  };

  let getTable = (t: t) =>
    ListLabels.map(t.players, ~f=p =>
      {
        id: Player.getId(p),
        cards: Player.getTable(p),
        score: Player.getScore(p),
      }
    );

  let getCurrentPlayerId = t => t |> getCurrentPlayer |> Player.getId;

  let getHand = (t: t) => t |> getCurrentPlayer |> Player.getHand;

  let select = (t, card) =>
    t |> getCurrentPlayer |> Player.select(card) |> setCurrentPlayer(t);

  let play = t => t |> getCurrentPlayer |> Player.play |> setCurrentPlayer(t);

  let showSelectedCard = t => t |> getCurrentPlayer |> Player.getSelected;

  let hasSelectedCard = t => showSelectedCard(t) != None;

  let rotateHand = players =>
    List.map(Player.getHand, players)
    |> Utils.rotate
    |> List.combine(players)
    |> List.map(((player, newHand)) => Player.nextRound(player, ~newHand));

  let calcThisRoundPoint = t => {
    let {players} = t;
    open Player.Scoring;
    let gCtx =
      ListLabels.fold_right(
        ~f=updateGameCtx,
        ~init=GameScoringCtx.newCtx(),
        players,
      );
    let players =
      ListLabels.map(
        ~f=p => scoreThisTurn(p, gCtx) |> updatePlayerCtx,
        players,
      );
    {...t, players};
  };

  let isRoundEnd = t => t.currentPlayer === List.length(t.players) - 1;

  let nextRound = (t: t) => {...t, players: rotateHand(t.players)};

  let isGameEnd = (t: t) => t |> getCurrentPlayer |> Player.isHandEmpty;

  let toString = (t: t) =>
    "(Game (CurrentPlayerIndex("
    ++ string_of_int(t.currentPlayer)
    ++ ")(Players"
    ++ Utils.string_of_list(t.players, ~f=Player.toString)
    ++ ")";
};
