module type S = {
  include Card.S;
  type nigiri;
};

module type N = {
  let num_points: int;
  let num_cards: int;
  let image: string;
  let name: string;
};

module Make: (N: N) => S;
