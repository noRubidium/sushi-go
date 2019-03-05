/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.statelessComponent("App");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~numPlayers, ~numCards, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => <GameComponent numPlayers numCards />,
};
