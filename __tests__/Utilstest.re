open Jest;

module List = {
  open Utils.List;
  describe("Utils.List.repeat", () => {
    open Expect;

    test("gives empty", () =>
      expect(repeat(0, ~f=n => n) |> List.length) |> toEqual(0)
    );
    test("gives three elements of numbers", () =>
      expect(repeat(3, ~f=n => n)) |> toEqual([1, 2, 3])
    );
  });

  describe("Utils.List.shuffle", () => {
    open Expect;
    Random.init(500);
    test("matches the target shuffling", () =>
      expect(shuffle([1, 2, 3, 4, 5])) |> toEqual([2, 1, 3, 4, 5])
    );
  });

  describe("Utils.List.splice", () => {
    open Expect;
    test("gives empty list", () =>
      expect(splice([], ~n=0)) |> toEqual(([], []))
    );

    test("gives a list of 1 element and a list of 3 elements", () =>
      expect(repeat(4, ~f=n => n) |> splice(~n=1))
      |> toEqual(([1], [2, 3, 4]))
    );

    test("gives a list of 3 element and a list of 3 elements", () =>
      expect(repeat(6, ~f=n => n) |> splice(~n=3))
      |> toEqual(([1, 2, 3], [4, 5, 6]))
    );
  });

  describe("Utils.List.updateNth", () => {
    open Expect;

    test("updates 1st element", () =>
      expect([1, 2, 3] |> updateNth(~n=0, ~e=4)) |> toEqual([4, 2, 3])
    );

    test("updates 2nd element", () =>
      expect([1, 2, 3] |> updateNth(~n=1, ~e=4)) |> toEqual([1, 4, 3])
    );
  });

  describe("Utils.List.rotate", () =>
    Expect.(
      test("rotates the list around", () =>
        expect([1, 2, 3] |> rotate) |> toEqual([2, 3, 1])
      )
    )
  );

  describe("Utils.List.getAll", () =>
    Expect.(
      test("getAll non-None elements", () =>
        expect(repeat(~f=n => n mod 2 == 1 ? Some(n) : None, 4) |> getAll)
        |> toEqual([1, 3])
      )
    )
  );
};

describe("Utils.hex_of_int", () => {
  open Expect;
  open! Utils;
  test("0123456789", () => {
    let list = List.repeat(10, ~f=n => n - 1);
    expect(List.map(hex_of_int, list))
    |> toEqual(List.map(string_of_int, list));
  });

  test("10 to 15", () =>
    expect(List.repeat(6, ~f=n => n + 9) |> List.map(hex_of_int))
    |> toEqual(["A", "B", "C", "D", "E", "F"])
  );

  test("255 to FF", () =>
    expect(hex_of_int(255)) |> toEqual("FF")
  );

  test("256 to 100", () =>
    expect(hex_of_int(256)) |> toEqual("100")
  );
});
