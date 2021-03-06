module type S = {
  include Card.S;
  type full_deck;
};

module Make:
  (
    Nigiri1: Nigiri.S,
    Nigiri2: Nigiri.S,
    Nigiri3: Nigiri.S,
    Special1: Special.S,
    Special2: Special.S,
    Roll: Roll.S,
    Appetizer1: Appetizer.S,
    Appetizer2: Appetizer.S,
    Appetizer3: Appetizer.S,
  ) =>
   S;
