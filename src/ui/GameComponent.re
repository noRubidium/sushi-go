
include GameController.Make();

module CardComponent = CardComponent.Make(D);
module BoardComponent = BoardComponent.Make(D, Game);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("GameComponent");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~numPlayers, ~numCards, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: initialState(numPlayers, numCards),

  /* State transitions */
  reducer,

  render: self => {
    let game = Getter.game(self.state);
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
