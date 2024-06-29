#include "affineTransform.h"

using namespace s21;

void AffineTransform::translation(double x, double y, double z) {
  for (int i = 1; i <= data_.count_of_vertices; ++i) {
    data_.matrix3d(i, 0) += x;
    data_.matrix3d(i, 1) += y;
    data_.matrix3d(i, 2) += z;
  }
}

void AffineTransform::rotation(double angle) {
  rotate_x(angle);
  rotate_y(angle);
  rotate_z(angle);
}

void AffineTransform::scalling(double zoom) {
  for (int i = 1; i <= data_.count_of_vertices; ++i) {
    data_.matrix3d(i, 0) *= zoom;
    data_.matrix3d(i, 1) *= zoom;
    data_.matrix3d(i, 2) *= zoom;
  }
}

void AffineTransform::rotate_x(double angle) {
  angle = (angle * M_PI) / 180;
  Matrix rotate_X(3, 3);
  rotate_X(0, 0) = 1;
  rotate_X(1, 1) = cos(angle);
  rotate_X(1, 2) = sin(angle);
  rotate_X(2, 1) = -sin(angle);
  rotate_X(2, 2) = cos(angle);
  data_.matrix3d.MulMatrix(rotate_X);
}

void AffineTransform::rotate_y(double angle) {
  angle = (angle * M_PI) / 180;
  Matrix rotate_Y(3, 3);
  rotate_Y(0, 0) = cos(angle);
  rotate_Y(0, 2) = -sin(angle);
  rotate_Y(1, 1) = 1;
  rotate_Y(2, 0) = sin(angle);
  rotate_Y(2, 2) = cos(angle);
  data_.matrix3d.MulMatrix(rotate_Y);
}

void AffineTransform::rotate_z(double angle) {
  angle = (angle * M_PI) / 180;
  Matrix rotate_Z(3, 3);
  rotate_Z(0, 0) = cos(angle);
  rotate_Z(0, 1) = sin(angle);
  rotate_Z(1, 0) = -sin(angle);
  rotate_Z(1, 1) = cos(angle);
  rotate_Z(2, 2) = 1;
  data_.matrix3d.MulMatrix(rotate_Z);
}