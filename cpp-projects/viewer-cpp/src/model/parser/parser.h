#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <locale.h>

#include "../matrix/matrix.h"
#include "../struct/struct.h"

namespace s21 {

using std::ifstream;
using std::string;

class Parser {
 public:
  Parser(data_t& data) : data_(data) {}
  ~Parser() {}

  int processInputData(string& fileName);
  void processVertices(ifstream& file);
  void processFacets(ifstream& file);
  void verticesToArray();
  void facetsToArray();

  const data_t& getData() const { return data_; }
  void printMatrix();
  void printPolygons();

 private:
  data_t& data_;
};
}  // namespace s21

#endif