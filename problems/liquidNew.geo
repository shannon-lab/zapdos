dom0Mult = 1e3;
dom1Mult = 1e7;
//dom0Mult = 1;
//dom1Mult = 1;

Point(1) = {0, 0, 0, 2e-9 * dom0Mult};
Point(3) = {.5e-3 * dom0Mult, 0, 0, 50e-6 * dom0Mult};
Line(2) = {1,3};
Point(8) = {1e-3 * dom0Mult, 0, 0, 1e-9 * dom0Mult};
Line(7) = {3,8};
Point(9) = {1e-3 * dom0Mult + 50e-9 * dom1Mult, 0, 0, 10e-9 * dom1Mult};
Line(8) = {8,9};
Point(10) = {1e-3 * dom0Mult + 100e-9 * dom1Mult, 0, 0, 10e-9 * dom1Mult};
Line(9) = {9,10};
Physical Line(0) = {2,7};
Physical Line(1) = {8,9};
