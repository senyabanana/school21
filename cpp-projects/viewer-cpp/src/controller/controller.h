#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/affineTransform/affineTransform.h"
#include "../model/parser/parser.h"
#include "../model/struct/struct.h"

namespace s21 {
class Controller {
 private:
  Parser parser_;
  AffineTransform transform_;
  data_t& data_;

 public:
  Controller(data_t& data) : parser_(data), transform_(data), data_(data) {}
  ~Controller() {}

  int processInputData(string& fileName);
  void verticesToArray();
  void facetsToArray();
  void translation(double x, double y, double z);
  void rotation(double angle);
  void scalling(double zoom);

  void printMatrix();

  data_t& getData() { return data_; }
};
}  // namespace s21
#endif
