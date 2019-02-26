open Jest;

open Utils;

describe("Utils.repeat", () => {
  open Expect;

  test("gives empty", () =>
    expect(repeat(0, ~f=n => n) |> List.length) |> toEqual(0));
  test("gives three elements of numbers", () => 
    expect(repeat(3, ~f=(n) => n)) |> toEqual([1, 2, 3]));
});
