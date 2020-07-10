dom0Mult = 1e4;
dom1Mult = 1e4;
dom2Mult = 1e4;

d0_length = 1e-4;
d1_length = 1e-4;
d2_length = 1e-4;

Point(1) = {0, 0, 0, 5e-6 * dom0Mult};
Point(2) = {d0_length * dom0Mult, 0, 0, 0.4e-6 * dom0Mult};
Point(3) = {d0_length * dom0Mult + (d1_length)/2 * dom1Mult, 0, 0, 6e-6 * dom1Mult};
Point(4) = {d0_length * dom0Mult + d1_length * dom1Mult, 0, 0, 0.4e-6 * dom1Mult};
Point(5) = {d0_length * dom0Mult + d1_length * dom1Mult + d2_length * dom2Mult, 0, 0, 5e-6 * dom2Mult};

Line(11) = {1,2};
Line(21) = {2,3};
Line(31) = {3,4};
Line(41) = {4,5};

Physical Line(0) = {11};
Physical Line(1) = {21,31};
Physical Line(2) = {41};
