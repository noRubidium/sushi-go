module D = Deck.Make(TamagoNigiri, SalmonNigiri, SquidNigiri);
module Game = Game.Make(D);

module CardComponent = CardComponent.Make(D);

/* State declaration */
type state = {
  game: Game.t,
};
  
/* Action declaration */
type action =
  | SelectCard(D.t)
  | PlayCard;

/* Component template declaration.
    Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("App");

/* greeting and children are props. `children` isn't used, therefore ignored.
    We ignore it by prepending it with an underscore */
let make = (~numPlayers, ~numCards, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => { game: Game.newGame(~numPlayers, ~numCards)},

  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | SelectCard(card) => ReasonReact.Update({ game: Game.select(state.game, card) });
    | PlayCard => ReasonReact.Update({ game: Game.play(state.game )});
    },

  render: self => {
    let { game } = self.state;
    <div>
      {"Game is: " ++ Game.toString(game) |> ReasonReact.string}
      <ListView 
        makeListItem={(card) => <CardComponent card={card} onClickHandler={(_event) => self.send(SelectCard(card))}/>} 
        cards={game |> Game.getHand |> Array.of_list}
      />
      <div>
        {game 
          |> Game.showSelectedCard 
          |> Option.map((card) => <CardComponent card={card} onClickHandler={Constants.noop1} />) 
          |> Option.map((e) => <div>{ReasonReact.string("Selected card is: ")}{e}</div>)
          |> Option.valueWithDefault(~default=(Constants.emptyElement))       
        }
      </div>
      <button onClick={(_event) => self.send(PlayCard)}>{"Play" |> ReasonReact.string}</button>
    </div>;
  },
};
