open Jest;

describe("ListComponent", () => {
  open Expect;
  test("renders a list of components", () => {
    let makeListItem = n => n |> string_of_int |> ReasonReact.string;
    let items = Utils.List.repeat(10, ~f=n => n) |> Array.of_list;
    let component = ReactShallowRenderer.renderWithRenderer(<ListView items makeListItem />);
    expect(component) |> toMatchSnapshot;
  });
  });
