module D =
  Deck.Make(TamagoNigiri, SalmonNigiri, SquidNigiri, Wasabi, Wasabi, Maki, Sashimi, Sashimi, Sashimi);
module Game = Game.Make(D);

module CardComponent = CardComponent.Make(D);
module BoardComponent = BoardComponent.Make(D);

/* State declaration */
type state = {game: Game.t};
/* Action declaration */
type action =
  | SelectCard(D.t)
  | PlayCard
  | Noop;

module GameCtrl = {
  let reducer = (action, state) =>
    switch (action) {
    | Noop => ReasonReact.NoUpdate;
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
};
/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("App");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~numPlayers, ~numCards, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {game: Game.newGame(~numPlayers, ~numCards)},

  /* State transitions */
  reducer: GameCtrl.reducer,

  render: self => {
    let {game} = self.state;
    <div>
      <div> {ReasonReact.string("Game Table")} <BoardComponent game /> </div>
      <div>
        {ReasonReact.string(Game.getCurrentPlayerId(game) ++ "'s hand:")}
        <ListView
          makeListItem={card =>
            <CardComponent
              card
              onClickHandler={_event => self.send(SelectCard(card))}
            />
          }
          items={game |> Game.getHand |> Array.of_list}
        />
      </div>
      <div>
        {game
         |> Game.showSelectedCard
         |> Option.map(card =>
              <CardComponent card onClickHandler=Constants.noop1 />
            )
         |> Option.map(e =>
              <div> {ReasonReact.string("Selected card is: ")} e </div>
            )
         |> Option.valueWithDefault(~default=Constants.emptyElement)}
      </div>
      <button onClick={_event => self.send(Game.isGameEnd(game) ? Noop : PlayCard)}>
        {(Game.isGameEnd(game) ? "End of Game" : "Play") |> ReasonReact.string}
      </button>
    </div>;
  },
};
