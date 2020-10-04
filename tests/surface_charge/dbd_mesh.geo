dom0Mult = 1e4;
dom1Mult = 1e4;

d0_length = 1e-4;
d1_length = 1e-4;

Point(1) = {0, 0, 0, 0.4e-6 * dom0Mult};
Point(2) = {(d0_length)/2 * dom0Mult, 0, 0, 4e-6 * dom0Mult};
Point(3) = {d0_length * dom0Mult, 0, 0, 0.1e-6 * dom0Mult};
Point(4) = {d0_length * dom0Mult + d1_length * dom1Mult, 0, 0, 5e-6 * dom1Mult};

Line(11) = {1,2};
Line(21) = {2,3};
Line(31) = {3,4};

Physical Line(0) = {11,21};
Physical Line(1) = {31};
