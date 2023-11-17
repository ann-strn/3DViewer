#include <check.h>

#include "../back/affine_transformations.h"
#include "../back/parser.h"

#define EPS 1e-07

START_TEST(parser_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";

  d = openObjFile(filename);
  ck_assert_int_eq(d->polygonCount, 10);
  ck_assert_int_eq(d->vertexCount, 8);
  int numberOfVericalesInPolygon[10][6] = {
      {0, 6, 6, 4, 4, 0}, {0, 2, 2, 6, 6, 0}, {0, 3, 3, 2, 2, 0},
      {0, 1, 1, 3, 3, 0}, {2, 7, 7, 6, 6, 2}, {2, 3, 3, 7, 7, 2},
      {4, 6, 6, 7, 7, 4}, {4, 7, 7, 5, 5, 4}, {0, 4, 4, 5, 5, 0},
      {0, 5, 5, 1, 1, 0}};
  for (int i = 0; i < d->polygonCount; ++i) {
    for (int j = 0; j < d->polygon[i].numberOfVerticesInPolygon; ++j) {
      ck_assert_int_eq(d->polygon[i].vertices[j],
                       numberOfVericalesInPolygon[i][j]);
    }
  }
  destructData(d);
}
END_TEST

START_TEST(parser_2) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";

  d = openObjFile(filename);
  ck_assert_int_eq(d->polygonCount, 12);
  ck_assert_int_eq(d->vertexCount, 8);
  int numberOfVericalesInPolygon[12][6] = {
      {4, 2, 2, 0, 0, 4}, {2, 7, 7, 3, 3, 2}, {6, 5, 5, 7, 7, 6},
      {1, 7, 7, 5, 5, 1}, {0, 3, 3, 1, 1, 0}, {4, 1, 1, 5, 5, 4},
      {4, 6, 6, 2, 2, 4}, {2, 6, 6, 7, 7, 2}, {6, 4, 4, 5, 5, 6},
      {1, 3, 3, 7, 7, 1}, {0, 2, 2, 3, 3, 0}, {4, 0, 0, 1, 1, 4}};
  for (int i = 0; i < d->polygonCount; ++i) {
    for (int j = 0; j < d->polygon[i].numberOfVerticesInPolygon; ++j) {
      ck_assert_int_eq(d->polygon[i].vertices[j],
                       numberOfVericalesInPolygon[i][j]);
    }
  }
  destructData(d);
}
END_TEST

START_TEST(parser_3) {
  Data *d = {0};
  const char filename[] = "tests/minus.obj";

  d = openObjFile(filename);
  ck_assert_int_eq(d->polygonCount, 10);
  ck_assert_int_eq(d->vertexCount, 8);
  int numberOfVericalesInPolygon[10][6] = {
      {0, 6, 6, 4, 4, 0}, {0, 2, 2, 6, 6, 0}, {0, 3, 3, 2, 2, 0},
      {0, 1, 1, 3, 3, 0}, {2, 7, 7, 6, 6, 2}, {2, 3, 3, 7, 7, 2},
      {4, 6, 6, 7, 7, 4}, {4, 7, 7, 5, 5, 4}, {0, 4, 4, 5, 5, 0},
      {0, 5, 5, 1, 1, 0}};
  for (int i = 0; i < d->polygonCount; ++i) {
    for (int j = 0; j < d->polygon[i].numberOfVerticesInPolygon; ++j) {
      ck_assert_int_eq(d->polygon[i].vertices[j],
                       numberOfVericalesInPolygon[i][j]);
    }
  }
  destructData(d);
}
END_TEST

START_TEST(find_Maxmin_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  ck_assert_ldouble_eq_tol(d->mnmx.xMax, 2.0, EPS);
  ck_assert_double_eq_tol(d->mnmx.xMin, 0.0, EPS);
  ck_assert_double_eq_tol(d->mnmx.yMax, 2.0, EPS);
  ck_assert_double_eq_tol(d->mnmx.yMin, 0.0, EPS);
  ck_assert_double_eq_tol(d->mnmx.zMax, 2.0, EPS);
  ck_assert_double_eq_tol(d->mnmx.zMin, 0.0, EPS);
}
END_TEST

START_TEST(find_Maxmin_2) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  ck_assert_ldouble_eq_tol(d->mnmx.xMax, 1.000000, EPS);
  ck_assert_double_eq_tol(d->mnmx.xMin, -1.000000, EPS);
  ck_assert_double_eq_tol(d->mnmx.yMax, 1.000000, EPS);
  ck_assert_double_eq_tol(d->mnmx.yMin, -1.000000, EPS);
  ck_assert_double_eq_tol(d->mnmx.zMax, 1.000000, EPS);
  ck_assert_double_eq_tol(d->mnmx.zMin, -1.000000, EPS);
}
END_TEST

START_TEST(centering_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);

  double scale = calculateScale(d);
  ck_assert_double_eq_tol(scale, 0.5, EPS);

  double centeredData[] = {-0.5, -0.5, -0.5, -0.5, -0.5, 0.5,  -0.5, 0.5,
                           -0.5, -0.5, 0.5,  0.5,  0.5,  -0.5, -0.5, 0.5,
                           -0.5, 0.5,  0.5,  0.5,  -0.5, 0.5,  0.5,  0.5};
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], centeredData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(centering_2) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);

  double scale = calculateScale(d);
  ck_assert_double_eq_tol(scale, 0.5, EPS);

  double centeredData[] = {
      0.500000,  0.500000, -0.500000, 0.500000,  -0.500000, -0.500000,
      0.500000,  0.500000, 0.500000,  0.500000,  -0.500000, 0.500000,
      -0.500000, 0.500000, -0.500000, -0.500000, -0.500000, -0.500000,
      -0.500000, 0.500000, 0.500000,  -0.500000, -0.500000, 0.500000};
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], centeredData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(find_max_of_tree_1) {
  double max, x = 2.3, y = -4.5, z = 0;
  max = findMaxOfTree(x, y, z);
  ck_assert_double_eq_tol(max, 2.3, EPS);
}
END_TEST

START_TEST(find_max_of_tree_2) {
  double max, x = 4.8, y = 7.5, z = 2;
  max = findMaxOfTree(x, y, z);
  ck_assert_double_eq_tol(max, 7.5, EPS);
}
END_TEST

START_TEST(find_max_of_tree_3) {
  double max, x = -1.5, y = 3.5, z = 1;
  max = findMaxOfTree(x, y, z);
  ck_assert_double_eq_tol(max, 3.5, EPS);
}
END_TEST

START_TEST(find_max_of_tree_4) {
  double max, x = 1.3, y = -3.8, z = 0;
  max = findMaxOfTree(x, y, z);
  ck_assert_double_eq_tol(max, 1.3, EPS);
}
END_TEST

START_TEST(moveX_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  double movedData[] = {4.5,  -0.5, -0.5, 4.5, -0.5, 0.5,  4.5,  0.5,
                        -0.5, 4.5,  0.5,  0.5, 5.5,  -0.5, -0.5, 5.5,
                        -0.5, 0.5,  5.5,  0.5, -0.5, 5.5,  0.5,  0.5};
  moveX(d, 5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveX_2) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  double movedData[] = {-5.5, -0.5, -0.5, -5.5, -0.5, 0.5,  -5.5, 0.5,
                        -0.5, -5.5, 0.5,  0.5,  -4.5, -0.5, -0.5, -4.5,
                        -0.5, 0.5,  -4.5, 0.5,  -0.5, -4.5, 0.5,  0.5};
  moveX(d, -5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveX_3) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  double movedData[] = {5.500000,  0.500000,  -0.500000, 5.500000, -0.500000,
                        -0.500000, 5.500000,  0.500000,  0.500000, 5.500000,
                        -0.500000, 0.500000,  4.500000,  0.500000, -0.500000,
                        4.500000,  -0.500000, -0.500000, 4.500000, 0.500000,
                        0.500000,  4.500000,  -0.500000, 0.500000};
  moveX(d, 5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveX_4) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  double movedData[] = {-4.500000, 0.500000,  -0.500000, -4.500000, -0.500000,
                        -0.500000, -4.500000, 0.500000,  0.500000,  -4.500000,
                        -0.500000, 0.500000,  -5.500000, 0.500000,  -0.500000,
                        -5.500000, -0.500000, -0.500000, -5.500000, 0.500000,
                        0.500000,  -5.500000, -0.500000, 0.500000};
  moveX(d, -5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveY_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  double movedData[] = {-0.5, 4.5,  -0.5, -0.5, 4.5,  0.5, -0.5, 5.5,
                        -0.5, -0.5, 5.5,  0.5,  0.5,  4.5, -0.5, 0.5,
                        4.5,  0.5,  0.5,  5.5,  -0.5, 0.5, 5.5,  0.5};
  moveY(d, 5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveY_2) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  double movedData[] = {-0.5, -5.5, -0.5, -0.5, -5.5, 0.5,  -0.5, -4.5,
                        -0.5, -0.5, -4.5, 0.5,  0.5,  -5.5, -0.5, 0.5,
                        -5.5, 0.5,  0.5,  -4.5, -0.5, 0.5,  -4.5, 0.5};
  moveY(d, -5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveY_3) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  double movedData[] = {0.500000,  5.500000,  -0.500000, 0.500000,  4.500000,
                        -0.500000, 0.500000,  5.500000,  0.500000,  0.500000,
                        4.500000,  0.500000,  -0.500000, 5.500000,  -0.500000,
                        -0.500000, 4.500000,  -0.500000, -0.500000, 5.500000,
                        0.500000,  -0.500000, 4.500000,  0.500000};
  moveY(d, 5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveY_4) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  double movedData[] = {0.500000,  -4.500000, -0.500000, 0.500000,  -5.500000,
                        -0.500000, 0.500000,  -4.500000, 0.500000,  0.500000,
                        -5.500000, 0.500000,  -0.500000, -4.500000, -0.500000,
                        -0.500000, -5.500000, -0.500000, -0.500000, -4.500000,
                        0.500000,  -0.500000, -5.500000, 0.500000};
  moveY(d, -5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveZ_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  double movedData[] = {-0.5, -0.5, 4.5, -0.5, -0.5, 5.5,  -0.5, 0.5,
                        4.5,  -0.5, 0.5, 5.5,  0.5,  -0.5, 4.5,  0.5,
                        -0.5, 5.5,  0.5, 0.5,  4.5,  0.5,  0.5,  5.5};
  moveZ(d, 5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveZ_2) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";
  d = openObjFile(filename);
  double movedData[] = {-0.5, -0.5, -5.5, -0.5, -0.5, -4.5, -0.5, 0.5,
                        -5.5, -0.5, 0.5,  -4.5, 0.5,  -0.5, -5.5, 0.5,
                        -0.5, -4.5, 0.5,  0.5,  -5.5, 0.5,  0.5,  -4.5};
  moveZ(d, -5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveZ_3) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  double movedData[] = {0.500000,  0.500000,  4.500000,  0.500000,  -0.500000,
                        4.500000,  0.500000,  0.500000,  5.500000,  0.500000,
                        -0.500000, 5.500000,  -0.500000, 0.500000,  4.500000,
                        -0.500000, -0.500000, 4.500000,  -0.500000, 0.500000,
                        5.500000,  -0.500000, -0.500000, 5.500000};
  moveZ(d, 5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(moveZ_4) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";
  d = openObjFile(filename);
  double movedData[] = {0.500000,  0.500000,  -5.500000, 0.500000,  -0.500000,
                        -5.500000, 0.500000,  0.500000,  -4.500000, 0.500000,
                        -0.500000, -4.500000, -0.500000, 0.500000,  -5.500000,
                        -0.500000, -0.500000, -5.500000, -0.500000, 0.500000,
                        -4.500000, -0.500000, -0.500000, -4.500000};
  moveZ(d, -5);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], movedData[i], EPS);
  }
  destructData(d);
}
END_TEST

START_TEST(rotateX_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";

  double rotatedData[] = {
      -0.5000000, -0.1830127, -0.6830127, -0.5000000, -0.5000000, 0.5000000,
      -0.5000000, 0.5000000,  -0.5000000, -0.5000000, -0.6830127, 0.1830127,
      0.5000000,  -0.5000000, -0.5000000, 0.5000000,  -0.5000000, 0.5000000,
      0.5000000,  0.6830127,  -0.1830127, 0.5000000,  0.5000000,  0.5000000};

  d = openObjFile(filename);
  rotateOX(d, 30);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], rotatedData[i], EPS);
  }
  // destructData(d);
}
END_TEST

START_TEST(rotateX_2) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";

  double rotatedData[] = {
      0.5000000,  0.6830127,  0.1830127,  0.5000000,  -0.5000000, -0.5000000,
      0.5000000,  0.5000000,  0.5000000,  0.5000000,  0.1830127,  -0.6830127,
      -0.5000000, 0.5000000,  -0.5000000, -0.5000000, -0.5000000, -0.5000000,
      -0.5000000, -0.1830127, 0.6830127,  -0.5000000, -0.5000000, 0.5000000};

  d = openObjFile(filename);
  rotateOX(d, 60);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], rotatedData[i], EPS);
  }
  // destructData(d);
}
END_TEST

START_TEST(rotateY_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";

  double rotatedData[] = {
      -0.6830127, -0.5000000, -0.1830127, -0.5000000, -0.5000000, 0.5000000,
      -0.5000000, 0.5000000,  -0.5000000, -0.1830127, 0.5000000,  0.6830127,
      0.5000000,  -0.5000000, -0.5000000, 0.5000000,  -0.5000000, 0.5000000,
      -0.6830127, 0.5000000,  -0.1830127, 0.5000000,  0.5000000,  0.5000000};

  d = openObjFile(filename);
  rotateOY(d, 30);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], rotatedData[i], EPS);
  }
  // destructData(d);
}
END_TEST

START_TEST(rotateY_2) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";

  double rotatedData[] = {
      -0.1830127, 0.5000000, -0.6830127, 0.5000000,  -0.5000000, -0.5000000,
      0.5000000,  0.5000000, 0.5000000,  -0.1830127, -0.5000000, -0.6830127,
      -0.5000000, 0.5000000, -0.5000000, -0.5000000, -0.5000000, -0.5000000,
      0.6830127,  0.5000000, -0.1830127, -0.5000000, -0.5000000, 0.5000000};

  d = openObjFile(filename);
  rotateOY(d, 60);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], rotatedData[i], EPS);
  }
  // destructData(d);
}
END_TEST

START_TEST(rotateZ_1) {
  Data *d = {0};
  const char filename[] = "tests/cube.obj";

  double rotatedData[] = {
      -0.1830127, -0.6830127, -0.5000000, -0.5000000, -0.5000000, 0.5000000,
      -0.5000000, 0.5000000,  -0.5000000, -0.1830127, -0.6830127, 0.5000000,
      0.5000000,  -0.5000000, -0.5000000, 0.5000000,  -0.5000000, 0.5000000,
      -0.1830127, 0.1830127,  -0.5000000, 0.5000000,  0.5000000,  0.5000000};

  d = openObjFile(filename);
  rotateOZ(d, 30);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], rotatedData[i], EPS);
  }
  // destructData(d);
}
END_TEST

START_TEST(rotateZ_2) {
  Data *d = {0};
  const char filename[] = "tests/cube_first.obj";

  double rotatedData[] = {
      -0.1830127, 0.6830127, -0.5000000, 0.5000000,  -0.5000000, -0.5000000,
      0.5000000,  0.5000000, 0.5000000,  -0.1830127, 0.1830127,  0.5000000,
      -0.5000000, 0.5000000, -0.5000000, -0.5000000, -0.5000000, -0.5000000,
      -0.1830127, 0.6830127, 0.5000000,  -0.5000000, -0.5000000, 0.5000000};

  d = openObjFile(filename);
  rotateOZ(d, 60);
  for (int i = 0; i < d->m.rows * 3; i++) {
    ck_assert_double_eq_tol(d->m.mtrx[i], rotatedData[i], EPS);
  }
  // destructData(d);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, parser_1);
  tcase_add_test(tc1_1, parser_2);
  tcase_add_test(tc1_1, parser_3);
  tcase_add_test(tc1_1, find_Maxmin_1);
  tcase_add_test(tc1_1, find_Maxmin_2);
  tcase_add_test(tc1_1, centering_1);
  tcase_add_test(tc1_1, centering_2);
  tcase_add_test(tc1_1, find_max_of_tree_1);
  tcase_add_test(tc1_1, find_max_of_tree_2);
  tcase_add_test(tc1_1, find_max_of_tree_3);
  tcase_add_test(tc1_1, find_max_of_tree_4);
  tcase_add_test(tc1_1, moveX_1);
  tcase_add_test(tc1_1, moveX_2);
  tcase_add_test(tc1_1, moveX_3);
  tcase_add_test(tc1_1, moveX_4);
  tcase_add_test(tc1_1, moveY_1);
  tcase_add_test(tc1_1, moveY_2);
  tcase_add_test(tc1_1, moveY_3);
  tcase_add_test(tc1_1, moveY_4);
  tcase_add_test(tc1_1, moveZ_1);
  tcase_add_test(tc1_1, moveZ_2);
  tcase_add_test(tc1_1, moveZ_3);
  tcase_add_test(tc1_1, moveZ_4);
  tcase_add_test(tc1_1, rotateX_1);
  tcase_add_test(tc1_1, rotateX_2);
  tcase_add_test(tc1_1, rotateY_1);
  tcase_add_test(tc1_1, rotateY_2);
  tcase_add_test(tc1_1, rotateZ_1);
  tcase_add_test(tc1_1, rotateZ_2);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
