/* This is the basic component. */
let component = ReasonReact.statelessComponent("ListView");

let make = (~makeHandleClick, ~cards, ~makeListItem, _children) => {
  ...component,
  render: self =>
    {Array.map((card) => 
      <div onClick={self.handle(makeHandleClick(card))}>
        {makeListItem(card)}
      </div>, cards
    )
    |> ReasonReact.array},
};
