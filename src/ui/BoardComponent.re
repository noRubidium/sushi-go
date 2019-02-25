module Styles = {
    open Css;

    let table = style([
        backgroundColor(Theme.Color.darkBlue),
        padding(Theme.gridBaseline(8)),
        margin(Theme.gridBaseline(8)),
    ]);

    let text = style([
        fontFamily("sans-serif"),
    ]);

    let m = style([
        backgroundColor(Theme.Color.lightBlue),
        padding(Theme.gridBaseline(8)),
        minHeight(Theme.gridBaseline(43)),
    ])
}

module Make = (D: Deck.S) => {
    module Game = Game.Make(D);

    module CardComponent = CardComponent.Make(D);

    let makePlayerTable = ({ id, cards }: Game.table) => <div className={Styles.table}>
        <div className={Styles.text}>{"Player (" ++ id ++ "):" |> ReasonReact.string}</div>
        <div className={Styles.m}>
            <ListView 
                items={cards |> Array.of_list} 
                makeListItem={card => <CardComponent card={card} onClickHandler={Constants.noop1}/>} 
            />
        </div>
    </div>;
 
    /* This is the basic component. */
    let component = ReasonReact.statelessComponent("BoardComponent");

    let make = (~game, _children) => {
    ...component,
    render: _self =>
    <div>
        {ReasonReact.string("Table: ")}
        {
            Game.getTable(game)
        |> List.map(makePlayerTable)
        |> Array.of_list
        |> ReasonReact.array
        }
    </div>
    };
}
