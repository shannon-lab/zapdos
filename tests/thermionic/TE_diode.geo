dom0Size = 50E-6;

Point(1) = {0             , 0, 0,  2E-4 * dom0Size};
Point(2) = {0.5 * dom0Size, 0, 0, 50E-4 * dom0Size};
Point(3) = {      dom0Size, 0, 0,  1E-4 * dom0Size};

Line(1) = {1,2};
Line(2) = {2,3};

Physical Line(0) = {1,2};
