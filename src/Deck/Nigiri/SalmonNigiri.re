module Base = {
    let num_points = 2;
    let num_cards = 10;
    let image = "salmonNigiri";
    let name = "SalmonNigiri";
};

include Nigiri.Make(Base);
