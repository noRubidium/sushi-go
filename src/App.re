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
    | PlayCard(D.t);
  
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
      | PlayCard(card) => 
        switch (Game.play(state.game, card)) {
        | Some(game) => ReasonReact.Update({ game: game })
        | None => ReasonReact.NoUpdate;
        };
      },
  
    render: self => {
      let message =
        "You've clicked this " ++ " times(s)";
      let game = "Game is: "  ++ Game.toString(self.state.game);
      <div>
        <button onClick={_event => self.send(Click)}>
          {ReasonReact.string(message)}
        </button>
        <button onClick={_event => self.send(Toggle)}>
          {ReasonReact.string("Toggle greeting")}
        </button>
        {ReasonReact.string(game)}
        <ListView 
          makeListItem={(c) => c |> D.toString |> ReasonReact.string} 
          cards={self.state.game |> Game.getHand |> Array.of_list}
          makeHandleClick={(card, _event, _handle) => self.send(PlayCard(card))}
        />
      </div>;
    },
  };
  