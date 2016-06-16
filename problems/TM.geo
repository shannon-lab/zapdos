// diameter of faraday cage = 3 cm -> radius of faraday cage = 1.5 cm
// Let's make launcher half the radius -> .75 cm = .0075 m
// Let's go with a length of 30 cm (or half the value of the low end from Graves paper)
// Recall that we're using a mirror plane

lc = .0075/20;
tl = .09;
// Origin
Point(1) = {0, 0, 0, lc};

// Middle of launcher
Point(2) = {.0075, 0, 0, lc};

// top right of launcher
Point(3) = {.0075, .0075 * .5, 0, lc};

// bottom right of Farady cage
Point(4) = {.015, .0075 * .5, 0, lc};

// top right of Faraday cage
Point(5) = {.015, tl, 0, lc};

// center axis of Faraday cage
Point(6) = {0, tl, 0, lc};

// Mirror plane
Line(2) = {1, 2};

// Antenna
Line(3) = {2, 3};

// Horiz PEC 2
Line(4) = {3, 4};

// Vert PEC
Line(5) = {4, 5};

// Horiz PEC 3
Line(6) = {5, 6};

// Axis of symmetry
Line(7) = {6, 1};

Line Loop(8) = {2, 3, 4, 5, 6, 7};
Plane Surface(9) = {8};

// Sim domain
Physical Surface(1) = {9};

// Axis
Physical Line("Axis") = {6};

// Mirror plane
Physical Line("Mirror") = {1};

// Antenna
Physical Line("Antenna") = {2};

// Horiz PECs
Physical Line("horiz_pecs") = {3, 5};

// Vert PEC
Physical Line("vert_pec") = {4};
