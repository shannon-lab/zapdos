dom0Mult = 1/25.4e-3;
//dom0Mult = 1;

Point(1) = {0, 0, 0, 2e-6};
Point(3) = {12.7e-3 * dom0Mult, 0, 0, 50e-3};
Line(2) = {1,3};
Point(8) = {25.4e-3 * dom0Mult, 0, 0, 1e-6};
Line(7) = {3,8};
Physical Line(0) = {2,7};
