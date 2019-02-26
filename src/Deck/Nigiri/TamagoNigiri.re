module Base = {
  let num_points = 1;
  let num_cards = 10;
  let image = "tamagoNigiri";
  let name = "TamagoNigiri";
};

include Nigiri.Make(Base);
