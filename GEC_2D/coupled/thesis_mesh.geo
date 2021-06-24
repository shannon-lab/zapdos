dom0Mult = 1/25.4e-3;

//Electrode Nodes
EN = 240;
//Insulator Nodes
//IN = 7;
IN = 3;
//Ground-to-Insulator Nodes
//GN = 11;
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
Point(2) = {200e-3 * dom0Mult, 63.5e-3 * dom0Mult, 0};

//Edge of Bottom Electrode
Point(3) = {200e-3 * dom0Mult, 38.1e-3 * dom0Mult, 0};

//Center of the Bottom electrode
Point(4) = {0, 38.1e-3 * dom0Mult, 0};

//Left Side Mid Point
Point(5) = {0, 50.8e-3 * dom0Mult, 0};

//Center Line Mid-ish Point
Point(6) = {200e-3 * dom0Mult, 50.8e-3 * dom0Mult, 0};

//Top Electrode
Line(101) = {1, 2};

//Right Wall
Line(102) = {2, 6};
Line(103) = {6, 3};

//Bottom Electrode
Line(104) = {3, 4};

// Axis of symmetry
Line(105) = {4, 5};
Line(106) = {5, 1};

//Mid Line
Line(107) = {5, 6};

//Structured Mesh: Top Plasma Half
Line Loop(201) = {101,102,-107,106};
Plane Surface(202) = {201};
Transfinite Surface {202} = {1, 2, 6, 5};
//Top_Electrode
Transfinite Line {101} = EN Using Progression 1;
//Top_Outer_Wall
Transfinite Line {102} = PN Using Progression 1;
//Mid_Line
Transfinite Line {107} = EN Using Progression 1;
//Top_Axis
Transfinite Line {106} = PN Using Progression 1;

//Structured Mesh: Bottom Plasma Half
Line Loop(203) = {107, 103, 104, 105};
Plane Surface(204) = {203};
Transfinite Surface {204} = {5, 6, 3, 4};
//Mid_Line
Transfinite Line {107} = EN Using Progression 1;
//Bottom_Outer_Wall
Transfinite Line {103} = PN Using Progression 1;
//Bottom_Electrode
Transfinite Line {104} = EN Using Progression 1;
//Bottom_Axis
Transfinite Line {105} = PN Using Progression 1;

Recombine Surface {202,204};

// Plasma domain
Physical Surface("plasma") = {202,204};

// Physical Top Electrode
Physical Line("Top_Electrode") = {101};

// Physical Bottom Electrode
Physical Line("Bottom_Electrode") = {104};

// Physical Walls
Physical Line("Walls") = {102,103};

// Physical axis of symmetry
Physical Line("axis") = {105,106};
