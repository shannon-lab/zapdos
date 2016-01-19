z = 0;

Point(1) = {z, z, z, 5e-9};
Point(2) = {0.5e-3, z, z, 10e-6};
Line(1) = {1,2};
Point(3) = {1e-3, z, z, 25e-9};
Line(2) = {2,3};
Physical Line(0) = {1,2};