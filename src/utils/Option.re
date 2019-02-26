type t('a) = option('a);

let map = (f, t) =>
  switch (t) {
  | Some(a) => Some(f(a))
  | None => None
  };

let bind = (f, t) =>
  switch (t) {
  | Some(a) => f(a)
  | None => None
  };

let valueWithDefault = (t, ~default) =>
  switch (t) {
  | Some(a) => a
  | None => default
  };

let toString = (t, ~f) =>
  switch (t) {
  | Some(a) => "(Some " ++ f(a) ++ ")"
  | None => "(None)"
  };
