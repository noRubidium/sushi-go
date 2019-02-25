

/* Styles */
module Styles = {
  open Css;

  let img = style([
    width(Theme.gridBaseline(20)),
    maxHeight(Theme.gridBaseline(20)),
    margin(auto),
  ]);

  let card = style([
    width(Theme.gridBaseline(35)),
    height(Theme.gridBaseline(50)),
    display(flexBox),
    backgroundColor(Theme.Color.darkGrey),
    border(Theme.gridBaseline(2), solid, Theme.Color.lightGrey),
    margin(Theme.gridBaseline(1)),
    borderRadius(Theme.gridBaseline(2)),
  ]);
}

module Make = (D: Deck.S) => {
    /* This is the basic component. */
    let component = ReasonReact.statelessComponent("CardComponent");

    let make = (~card, ~onClickHandler, _children) => {
    ...component,
    render: _self =>
        (<div className={Styles.card} onClick={onClickHandler}><img className={Styles.img} src={D.getImage(card)}/></div>)
    };
}
