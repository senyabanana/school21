#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include <cmath>

#include "../matrix/matrix.h"
#include "../struct/struct.h"

namespace s21 {
class AffineTransform {
 public:
  AffineTransform(data_t& data) : data_(data) {}
  ~AffineTransform() {}

  void translation(double x, double y, double z);
  void rotation(double angle);
  void scalling(double zoom);
  void rotate_x(double angle);
  void rotate_y(double angle);
  void rotate_z(double angle);

 private:
  data_t& data_;
};
}  // namespace s21

#endif