module Base = {
  let num_points = 3;
  let num_cards = 10;
  let image = "squidNigiri";
  let name = "SquidNigiri";
};

include Nigiri.Make(Base);
