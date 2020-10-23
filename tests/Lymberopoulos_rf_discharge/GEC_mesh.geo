dom0Mult = 1/25.4e-3;

lc = 5e-3;
dc = 5e-2;

//Center of the Top electrode
Point(1) = {0, 63.5e-3 * dom0Mult, 0, lc};

//Edge of Top Electrode
Point(2) = {50.8e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0, lc};

//Edge of Top Insulator
Point(3) = {52.3e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0, lc};

////Edge of Top Ground Wall
Point(13) = {53.8e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0, lc};

//Top Left of Rectangle
Point(4) = {53.8e-3 * dom0Mult, 101.6e-3 * dom0Mult, 0, dc};

//Top Right of Rectangle
Point(5) = {101.6e-3 * dom0Mult, 101.6e-3 * dom0Mult, 0, dc};

//Bottom Right of Rectangle
Point(6) = {101.6e-3 * dom0Mult, 0, 0, dc};

//Bottom Left of Rectangle
Point(7) = {53.8e-3 * dom0Mult, 0, 0, dc};

//Edge of Bottom Ground Wall
Point(18) = {53.8e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0, lc};

//Edge of Bottom Insulator
Point(8) = {52.3e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0, lc};

//Edge of Bottom Electrode
Point(9) = {50.8e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0, lc};

//Center of the Bottom electrode
Point(10) = {0, 38.1e-3 * dom0Mult, 0, lc};

//Top Electrode
Line(11) = {1, 2};

//Top Insulator
Line(12) = {2, 3};

//Ground Wall
Line(113) = {3, 13};
Line(13) = {13, 4};
Line(14) = {4, 5};
Line(15) = {5, 6};
Line(16) = {6, 7};
Line(17) = {7, 18};
Line(117) = {18, 8};

//Bottom Insulator
Line(18) = {8, 9};

//Bottom Electrode
Line(19) = {9, 10};

// Axis of symmetry
Line(20) = {10, 1};

//Plasma
Line Loop(30) = {11, 12, 113, 13, 14, 15, 16, 17, 117, 18, 19, 20};
Plane Surface(31) = {30};

// Plasma domain
Physical Surface("plasma") = {31};

// Physical Top Electrode
Physical Line("Top_Electrode") = {11};

// Physical Bottom Electrode
Physical Line("Bottom_Electrode") = {19};

// Physical Top Insulator
Physical Line("Top_Insulator") = {12};

// Physical Bottom Insulator
Physical Line("Bottom_Insulator") = {18};

// Physical Walls
Physical Line("Walls") = {113, 13, 14, 15, 16, 17, 117};

// Physical axis of symmetry
Physical Line("axis") = {20};
