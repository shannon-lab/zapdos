dom0Mult = 1/25.4e-3;

//Electrode Nodes
EN = 60;
//Insulator Nodes
IN = 3;
//Ground-to-Insulator Nodes
GN = 3;
//Plasma Side Nodes
PN = 11;
//Chamber Top-Bottom Nodes
TN = 31;
//TN = 62;
//Chamber Side Nodes
SN = 16;
//SN = 32;

//Center of the Top electrode
Point(1) = {0, 63.5e-3 * dom0Mult, 0};

//Edge of Top Electrode
Point(2) = {50.8e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Edge of Top Insulator
Point(3) = {52.3e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Edge of Top Ground Wall
Point(4) = {53.8e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Top Left of Rectangle
Point(5) = {53.8e-3 * dom0Mult, 101.6e-3 * dom0Mult, 0};

//Top Right of Rectangle
Point(6) = {101.6e-3 * dom0Mult, 101.6e-3 * dom0Mult, 0};

//Right Side Mid Point
Point(7) = {101.6e-3 * dom0Mult, 50.8e-3 * dom0Mult, 0};

//Bottom Right of Rectangle
Point(8) = {101.6e-3 * dom0Mult, 0, 0};

//Bottom Left of Rectangle
Point(9) = {53.8e-3 * dom0Mult, 0, 0};

//Edge of Bottom Ground Wall
Point(10) = {53.8e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Edge of Bottom Insulator
Point(11) = {52.3e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Edge of Bottom Electrode
Point(12) = {50.8e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Center of the Bottom electrode
Point(13) = {0, 38.1e-3 * dom0Mult, 0};

//Left Side Mid Point
Point(14) = {0, 50.8e-3 * dom0Mult, 0};

//Center Line Mid-ish Point
Point(15) = {53.8e-3 * dom0Mult, 50.8e-3 * dom0Mult, 0};

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
Line(113) = {13, 14};
Line(114) = {14, 1};

//Mid Line
Line(115) = {14, 15};
Line(116) = {15, 7};
//Mid Line Top Right Sides
Line(117) = {4, 15};
//Mid Line Bottom Right Sides
Line(119) = {10, 15};

//Structured Mesh: Top Plasma Half
Line Loop(201) = {101,102,103,117,-115,114};
Plane Surface(202) = {201};
Transfinite Surface {202} = {1, 4, 15, 14};
//Top_Electrode
Transfinite Line {101} = EN Using Progression 1;
//Top_Insulator
Transfinite Line {102} = IN Using Progression 1;
//Top_Ground
Transfinite Line {103} = GN Using Progression 1;
//Mid_Line
Transfinite Line {115} = (EN+IN+GN-2) Using Progression 1;
//Top_Left
Transfinite Line {-114} = PN Using Progression 1;
//Top_Right
Transfinite Line {117} = PN Using Progression 1;

//Structured Mesh: Bottom Plasma Half
Line Loop(203) = {110,111,112,113,115,-119};
Plane Surface(204) = {203};
Transfinite Surface {204} = {14, 15, 10, 13};
//Bottom_Electrode
Transfinite Line {112} = EN Using Progression 1;
//Bottom_Insulator
Transfinite Line {111} = IN Using Progression 1;
//Bottom_Ground
Transfinite Line {110} = GN Using Progression 1;
//Mid_Line
Transfinite Line {115} = (EN+IN+GN-2) Using Progression 1;
//Bottom_Left
Transfinite Line {113} = PN Using Progression 1;
//Bottom_Right
Transfinite Line {119} = PN Using Progression 1;

//Structured Mesh: Chamber
Line Loop(205) = {-117,104,105,106,107,108,109,119};
Plane Surface(206) = {205};
Transfinite Surface {206} = {5, 6, 8, 9};
//Top
Transfinite Line {105} = TN Using Progression 1;
//Right
Transfinite Line {106} = (PN+SN-1) Using Progression 1;
Transfinite Line {107} = (PN+SN-1) Using Progression 1;
//Bottom
Transfinite Line {108} = TN Using Progression 1;
//Left
Transfinite Line {109} = SN Using Progression 1;
Transfinite Line {119} = PN Using Progression 1;
Transfinite Line {117} = PN Using Progression 1;
Transfinite Line {104} = SN Using Progression 1;

Recombine Surface {202,204,206};

// Plasma domain
Physical Surface("plasma") = {202,204,206};

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
Physical Line("axis") = {113,114};
