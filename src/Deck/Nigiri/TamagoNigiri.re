module Base = {
    let num_points = 1;
    let num_cards = 10;
    let image = "None";
    let name = "TamagoNigiri";
};

include Nigiri.Make(Base);
