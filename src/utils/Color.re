type t = {
    r: int,
    g: int, 
    b: int
};

let red = { r: 255, g: 0, b: 0};
let blue = { r: 0, g: 0, b: 255};
let green = { r: 0, g: 255, b: 0};

let toHTMLColor = ({ r, g, b }) => "#" ++ Utils.hex_of_int(r) ++ Utils.hex_of_int(g) ++ Utils.hex_of_int(b);
