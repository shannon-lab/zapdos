z = 0;
// dom1Mult = 1e3;
// dom2Mult = 1e7;
dom1Mult = 1;
dom2Mult = 1;

Point(1) = {z, z, z, 2e-9 * dom1Mult};
Point(3) = {.5e-3 * dom1Mult, z, z, 50e-6 * dom1Mult};
Line(2) = {1,3};
Point(8) = {1e-3 * dom1Mult, z, z, 1e-9 * dom1Mult};
Line(7) = {3,8};
Point(9) = {1e-3 * dom1Mult + 50e-9 * dom2Mult, z, z, 10e-9 * dom2Mult};
Line(8) = {8,9};
Point(10) = {1e-3 * dom1Mult + 100e-9 * dom2Mult, z, z, 10e-9 * dom2Mult};
Line(9) = {9,10};
Physical Line(0) = {2,7};
Physical Line(1) = {8,9};
