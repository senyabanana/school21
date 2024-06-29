#include <gtest/gtest.h>

#include <cmath>

#include "../controller/controller.h"
#include "../model/matrix/matrix.h"

using namespace s21;

data_t data;

Controller controller(data);

TEST(MatrixTest, Transpose) {
  Matrix matrix(2, 2);

  int counter = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix(i, j) = counter++;
    }
  }

  matrix.Transpose();
  EXPECT_EQ(matrix(0, 0), 1);
  EXPECT_EQ(matrix(0, 1), 3);
  EXPECT_EQ(matrix(1, 0), 2);
  EXPECT_EQ(matrix(1, 1), 4);
}

TEST(MatrixTest, ProcessInputDataCube) {
  data_t data;
  // Controller controller;
  std::string filePath = "./objects/cube.obj";
  int result = controller.processInputData(filePath);
  EXPECT_EQ(controller.getData().count_of_vertices, 8);
  EXPECT_EQ(controller.getData().count_of_facets, 6);
  EXPECT_EQ(result, 0);
}

TEST(MatrixTest, ProcessInputDataBall) {
  data_t data;
  std::string filePath = "./objects/ball.obj";
  int result = controller.processInputData(filePath);
  EXPECT_EQ(controller.getData().count_of_vertices, 9667);
  EXPECT_EQ(controller.getData().count_of_facets, 9344);
  EXPECT_EQ(result, 0);
}

TEST(MatrixTest, ProcessInputDataCar) {
  data_t data;
  std::string filePath = "./objects/car.obj";
  int result = controller.processInputData(filePath);
  EXPECT_EQ(controller.getData().count_of_vertices, 1485);
  EXPECT_EQ(controller.getData().count_of_facets, 1352);
  EXPECT_EQ(result, 0);
}

TEST(MatrixTest, ProcessInputDataIncorrectFile) {
  data_t data;
  std::string filePath = "./objects/cubeeeee.obj";
  int result = controller.processInputData(filePath);
  EXPECT_EQ(result, -1);
}

TEST(MatrixTest, RotationX) {
  data_t data;
  std::string filePath = "./objects/pyramid.obj";
  controller.processInputData(filePath);
  double x = 10;
  controller.rotation(x);

  Matrix expectedMatrix(6, 3);
  double expMatrix[6][3] = {{0.0, 0.0, 0.0},
                            {-0.141314, 0.975082, 0.17101},
                            {-1.16841, -0.0296956, -0.796198},
                            {0.771281, 0.312325, -1.14349},
                            {1.16841, 0.0296956, 0.796198},
                            {-0.771281, -0.312325, 1.14349}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expectedMatrix(i, j) = expMatrix[i][j];
    }
  }

  EXPECT_TRUE(expectedMatrix.EqMatrix(controller.getData().matrix3d));
}

TEST(MatrixTest, Scalling) {
  data_t data;
  std::string filePath = "./objects/pyramid.obj";
  controller.processInputData(filePath);
  controller.scalling(2);

  Matrix expectedMatrix(6, 3);
  double expMatrix[6][3] = {{0.0, 0.0, 0.0},   {0.0, 2.0, 0.0},
                            {-2.0, 0.0, -2.0}, {2.0, 0.0, -2.0},
                            {2.0, 0.0, 2.0},   {-2.0, 0.0, 2.0}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expectedMatrix(i, j) = expMatrix[i][j];
    }
  }

  EXPECT_TRUE(expectedMatrix.EqMatrix(controller.getData().matrix3d));
}

TEST(MatrixTest, Translation) {
  data_t data;
  std::string filePath = "./objects/pyramid.obj";
  controller.processInputData(filePath);
  controller.translation(2, 3, 4);

  Matrix expectedMatrix(6, 3);
  double expMatrix[6][3] = {{0.0, 0.0, 0.0}, {2.0, 4.0, 4.0}, {1.0, 3.0, 3.0},
                            {3.0, 3.0, 3.0}, {3.0, 3.0, 5.0}, {1.0, 3.0, 5.0}};

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 3; j++) {
      expectedMatrix(i, j) = expMatrix[i][j];
    }
  }

  EXPECT_TRUE(expectedMatrix.EqMatrix(expectedMatrix));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
