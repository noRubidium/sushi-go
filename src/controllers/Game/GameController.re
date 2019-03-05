
module type S = {
  module D: Deck.S;

  module Game: Game.S with type deck := D.t;

  type state;

  type action =
    | SelectCard(D.t)
    | PlayCard
    | Noop;

  let initialState: (int, int, unit) => state;
  
  let reducer: (action, state) => ReasonReact.update(state, 'a, 'b);

  module Getter: {
    let game: state => Game.t;
  }
}

module Make: (() => S) = () => {
  module D =
    Deck.Make(
      TamagoNigiri,
      SalmonNigiri,
      SquidNigiri,
      Wasabi,
      Wasabi,
      Maki,
      Sashimi,
      Sashimi,
      Sashimi,
    );
  module Game = Game.Make(D);

  /* State declaration */
  type state = {game: Game.t};

  let initialState = (numPlayers, numCards, ()) => {game: Game.newGame(~numPlayers, ~numCards)};
  /* Action declaration */
  type action =
    | SelectCard(D.t)
    | PlayCard
    | Noop;

  let reducer = (action, state) =>
    switch (action) {
    | Noop => ReasonReact.NoUpdate
    | SelectCard(card) =>
      ReasonReact.Update({game: Game.select(state.game, card)})
    | PlayCard =>
      let game = state.game |> Game.play;
      let game =
        Game.isRoundEnd(game) ?
          game |> Game.calcThisRoundPoint |> Game.nextRound : game;
      let game =
        Game.isRoundEnd(game) && Game.isGameEnd(game) ?
          game |> Game.tallyGameEnd : game;
      ReasonReact.Update({game: game |> Game.nextPlayer});
    };

    module Getter = {
      let game = ({ game }) => game;
    }
  }
