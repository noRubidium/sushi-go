module Styles = {
  open Css;

  let list = style([
    display(flexBox),
    flexWrap(wrap),
  ])
}

/* This is the basic component. */
let component = ReasonReact.statelessComponent("ListView");

let make = (~cards, ~makeListItem, _children) => {
  ...component,
  render: _self =>
    <div className={Styles.list}> {Array.map(makeListItem, cards) |> ReasonReact.array}</div>,
};
