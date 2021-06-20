dom0Mult = 1/25.4e-3;

//Electrode Nodes
EN = 240;
//Insulator Nodes
IN = 3;
//Ground-to-Insulator Nodes
GN = 3;
//Plasma Side Nodes
PN = 7;
//Chamber Top-Bottom Nodes
TN = 31;
//TN = 62;
//Chamber Side Nodes
SN = 16;
//SN = 32;
//Sheath nodes
SHN = 15;

//Center of the Top electrode
Point(1) = {0, 63.5e-3 * dom0Mult, 0};

//Edge of Top Electrode
Point(2) = {200e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Edge of Top Insulator
Point(3) = {201.5e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Edge of Top Ground Wall
Point(4) = {203e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Top Left of Rectangle
Point(5) = {203e-3 * dom0Mult, 101.6e-3 * dom0Mult, 0};

//Top Right of Rectangle
Point(6) = {301.6e-3 * dom0Mult, 101.6e-3 * dom0Mult, 0};

//Right Side Mid Point
Point(7) = {301.6e-3 * dom0Mult, 50.8e-3 * dom0Mult, 0};

//Bottom Right of Rectangle
Point(8) = {301.6e-3 * dom0Mult, 0, 0};

//Bottom Left of Rectangle
Point(9) = {203e-3 * dom0Mult, 0, 0};

//Edge of Bottom Ground Wall
Point(10) = {203e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Edge of Bottom Insulator
Point(11) = {201.5e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Edge of Bottom Electrode
Point(12) = {200e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Center of the Bottom electrode
Point(13) = {0, 38.1e-3 * dom0Mult, 0};

//Left Side Mid Point
Point(14) = {0, 50.8e-3 * dom0Mult, 0};

//Center Line Mid-ish Point
Point(15) = {203e-3 * dom0Mult, 50.8e-3 * dom0Mult, 0};

// Upper sheath left point
Point(16) = {0, 58.4e-3 * dom0Mult, 0};
// Upper sheath right point
Point(17) = {203e-3 * dom0Mult, 58.4e-3 * dom0Mult, 0};
// Lower sheath left point
Point(18) = {0, 43.18e-3 * dom0Mult, 0};
// Lower sheath right point
Point(19) = {203e-3 * dom0Mult, 43.18e-3 * dom0Mult, 0};

//Top Electrode
Line(101) = {1, 2};

//Top Insulator
Line(102) = {2, 3};

//Ground Wall
Line(103) = {3, 4};
Line(104) = {4, 5};
Line(105) = {5, 6};
Line(106) = {6, 7};
Line(107) = {7, 8};
Line(108) = {8, 9};
Line(109) = {9, 10};
Line(110) = {10, 11};

//Bottom Insulator
Line(111) = {11, 12};

//Bottom Electrode
Line(112) = {12, 13};

// Axis of symmetry
Line(113) = {13, 18};
Line(114) = {18, 14};
Line(115) = {14, 16};
Line(116) = {16, 1};

//Mid Line
Line(117) = {14, 15};
Line(118) = {15, 7};
//Mid Line Top Right Sides
Line(119) = {4, 17}; // Top sheath side
Line(120) = {17, 15};
//Mid Line Bottom Right Sides
Line(121) = {10, 19}; // Bottom sheath side
Line(122) = {19, 15};

//Top Sheath
Line(123) = {16, 17};
//Bottom Sheath
Line(124) = {18, 19};

//Structured Mesh: Top Sheath
Line Loop(201) = {101, 102, 103, 119, -123, 116};
Plane Surface(202) = {201};
Transfinite Surface {202} = {1, 4, 17, 16};
//Top_Electrode
Transfinite Line {101} = EN Using Progression 1;
//Top_Insulator
Transfinite Line {102} = IN Using Progression 1;
//Top_Ground
Transfinite Line {103} = GN Using Progression 1;
//Sheath_Line
Transfinite Line {123} = (EN+IN+GN-2) Using Progression 1;
//Sheath_left
Transfinite Line {-116} = SHN Using Progression 1;
//Sheath_right
Transfinite Line {119} = SHN Using Progression 1;

//Structured Mesh: Top Plasma Half
Line Loop(203) = {123, 120, -117, 115};
Plane Surface(204) = {203};
Transfinite Surface {204} = {16, 17, 15, 14};
//Top_Sheath_Boundary
Transfinite Line {123} = (EN+IN+GN-2) Using Progression 1;
//Mid_Line
Transfinite Line {117} = (EN+IN+GN-2) Using Progression 1;
//Top_Left
Transfinite Line {-115} = PN Using Progression 1;
//Top_Right
Transfinite Line {120} = PN Using Progression 1;

//Structured Mesh: Bottom Plasma Half
Line Loop(205) = {117, -122, -124, 114};
Plane Surface(206) = {205};
Transfinite Surface {206} = {14, 15, 19, 18};
//Bottom_Sheath_Boundary
Transfinite Line {112} = (EN+IN+GN-2) Using Progression 1;
//Mid_Line
Transfinite Line {117} = (EN+IN+GN-2) Using Progression 1;
//Bottom_Left
Transfinite Line {114} = PN Using Progression 1;
//Bottom_Right
Transfinite Line {122} = PN Using Progression 1;

//Structured Mesh: Bottom Sheath
Line Loop(207) = {124, -121, 110, 111, 112, 113};
Plane Surface(208) = {207};
Transfinite Surface {208} = {13, 18, 19, 10};
//Bottom_Electrode
Transfinite Line {112} = EN Using Progression 1;
//Bottom_Insulator
Transfinite Line {111} = IN Using Progression 1;
//Bottom_Ground
Transfinite Line {110} = GN Using Progression 1;
//Sheath_Line
Transfinite Line {124} = (EN+IN+GN-2) Using Progression 1;
//Sheath_left
Transfinite Line {-113} = SHN Using Progression 1;
//Sheath_right
Transfinite Line {121} = SHN Using Progression 1;

//Structured Mesh: Chamber
Line Loop(209) = {-120, -119, 104, 105, 106, 107, 108, 109, 121, 122};
Plane Surface(210) = {209};
Transfinite Surface {210} = {5, 6, 8, 9};
//Top
Transfinite Line {105} = TN Using Progression 1;
//Right
Transfinite Line {106} = (PN+SHN+SN-2) Using Progression 1;
Transfinite Line {107} = (PN+SHN+SN-2) Using Progression 1;
//Bottom
Transfinite Line {108} = TN Using Progression 1;
//Left
Transfinite Line {109} = SN Using Progression 1;
Transfinite Line {121} = SHN Using Progression 1;
Transfinite Line {122} = PN Using Progression 1;
Transfinite Line {-120} = PN Using Progression 1;
Transfinite Line {-119} = SHN Using Progression 1;
Transfinite Line {104} = SN Using Progression 1;

Recombine Surface {202,204,206,208,210};

// Plasma domain
Physical Surface("plasma") = {202,204,206,208,210};

// Physical Top Electrode
Physical Line("Top_Electrode") = {101};

// Physical Bottom Electrode
Physical Line("Bottom_Electrode") = {112};

// Physical Top Insulator
Physical Line("Top_Insulator") = {102};

// Physical Bottom Insulator
Physical Line("Bottom_Insulator") = {111};

// Physical Walls
Physical Line("Walls") = {103,104,105,106,107,108,109,110};

// Physical axis of symmetry
Physical Line("axis") = {113,114,115,116};
