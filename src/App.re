module D = Deck.Make(TamagoNigiri, SalmonNigiri, SquidNigiri);
module Game = Game.Make(D);

/* Initialize UI Components */
module ListItem = ListItem.Make(D); 

/* State declaration */
type state = {
  game: Game.t,
};
  
  /* Action declaration */
  type action =
    | Click
    | Toggle
    | SelectCard(D.t)
    | PlayCard;
  
  /* Component template declaration.
     Needs to be **after** state and action declarations! */
  let component = ReasonReact.reducerComponent("Example");
  
  /* greeting and children are props. `children` isn't used, therefore ignored.
     We ignore it by prepending it with an underscore */
  let make = (~numPlayers, ~numCards, _children) => {
    /* spread the other default fields of component here and override a few */
    ...component,
  
    initialState: () => { game: Game.newGame(~numPlayers, ~numCards)},
  
    /* State transitions */
    reducer: (action, state) =>
      switch (action) {
      | Click => ReasonReact.Update({game: Game.nextRound(state.game)})
      | Toggle => ReasonReact.NoUpdate; /*ReasonReact.Update({...state })*/
      | SelectCard(card) => ReasonReact.Update({ game: Game.select(state.game, card) });
      | PlayCard => ReasonReact.Update({ game: Game.play(state.game )});
      },
  
    render: self => {
      let { game } = self.state;
      <div>
        {"Game is: " ++ Game.toString(game) |> ReasonReact.string}
        <ListView 
          makeListItem={(c) => <button>{c |> D.toString |> ReasonReact.string}</button>} 
          cards={game |> Game.getHand |> Array.of_list}
          makeHandleClick={(card, _event, _handle) => self.send(SelectCard(card))}
        />
        {(Game.hasSelectedCard(game) ? "Selected card is: " ++ Game.showSelectedCard(game) : "") |> ReasonReact.string}
        <button onClick={(_event) => self.send(PlayCard)}>{"Play" |> ReasonReact.string}</button>
      </div>;
    },
  };
  