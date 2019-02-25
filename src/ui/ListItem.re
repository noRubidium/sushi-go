module Make = (D: Deck.S) => {
    /* This is the basic component. */
    let component = ReasonReact.statelessComponent("ListItem");

    let make = (~card, _children) => {
    ...component,
    render: _self => card |> D.toString |> ReasonReact.string,
    };

}
