dom0Mult = 1e3;
dom1Mult = 1e7;
// dom0Mult = 1;
// dom1Mult = 1;

Point(1) = {0, 0, 0, dom0Mult};
Point(8) = {1e-3 * dom0Mult, 0, 0, dom0Mult};
Line(7) = {1,8};
Point(10) = {1e-3 * dom0Mult + 100e-9 * dom1Mult, 0, 0, dom1Mult};
Line(9) = {8,10};
Physical Line(0) = {7};
Physical Line(1) = {9};
