dom0Mult = 1;
dom1Mult = 1;

Point(1) = {0, 0, 0, 1e-6 * dom0Mult};
Point(3) = {.5e-3 * dom0Mult, 0, 0, 50e-6 * dom0Mult};
Line(2) = {1,3};
Point(8) = {1e-3 * dom0Mult, 0, 0, 1e-6 * dom0Mult};
Line(7) = {3,8};
Physical Line(0) = {2,7};
