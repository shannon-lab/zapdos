z = 0;

Point(1) = {z, z, z, 2e-9};
Point(3) = {.5e-3, z, z, 50e-6};
Line(2) = {1,3};
Point(8) = {1e-3, z, z, 1e-9};
Line(7) = {3,8};
Point(9) = {1e-3 + 50e-9, z, z, 10e-9};
Line(8) = {8,9};
Point(10) = {1e-3 + 100e-9, z, z, 10e-9};
Line(9) = {9,10};
Physical Line(0) = {2,7};
Physical Line(1) = {8,9};
