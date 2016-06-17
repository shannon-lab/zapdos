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

// center of mirror plane
Point(7) = {.0075/2, 0, 0, lc};

// Top right of dieletric
Point(8) = {.0075/2, tl, 0, lc};

// Mirror plane, dielectric
Line(2) = {1, 7};

// Mirror plane, vacuum
Line(8) = {7, 2};

// Antenna
Line(3) = {2, 3};

// Horiz PEC 2
Line(4) = {3, 4};

// Vert PEC
Line(5) = {4, 5};

// Top launcher, vacuum
Line(6) = {5, 8};

// Top launcher, dielectric
Line(9) = {8, 6};

// Axis of symmetry
Line(7) = {6, 1};

// Dielectric, vacuum divider
Line(10) = {8, 7};

// Dieletric
Line Loop(10) = {2, -10, 9, 7};
Plane Surface(11) = {10};

// Vacuum
Line Loop(8) = {8, 3, 4, 5, 6, 10};
Plane Surface(9) = {8};

// Sim domain
Physical Surface(0) = {9}; // Vacuum
Physical Surface(1) = {11}; // Dielectric

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
