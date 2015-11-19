Point(1) = {0, 0, 0, 1.0};
Point(2) = {0, 0, 0, 1.0};
Point(3) = {-0, 2.2, 0, 1.0};
Point(4) = {-0.5, 1.4, 0, 1.0};
Line(1) = {3, 4};
Point(5) = {0.2, 1.8, 0, 1.0};
Point(6) = {0.1, 1.1, 0, 1.0};
Delete {
  Point{1};
}
Delete {
  Point{2, 6};
}
Point(6) = {0, 1.4, -0, 1.0};
Line(2) = {6, 5};
Line(3) = {3, 5};
Line(4) = {4, 6};
Line Loop(5) = {1, 4, 2, -3};
Plane Surface(6) = {5};
