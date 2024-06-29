#ifndef STRUCT_H
#define STRUCT_H

#include <vector>

#include "../matrix/matrix.h"

namespace s21 {

using std::vector;

typedef struct polygon_t {
  polygon_t()
      : vertices(std::vector<int>()), numbers_of_vertices_in_facets(0) {}
  vector<int> vertices;
  int numbers_of_vertices_in_facets;
} polygon_t;

typedef struct data_t {
  data_t() : count_of_vertices(0), count_of_facets(0) {}
  ~data_t() {}

 public:
  int count_of_vertices;
  int count_of_facets;
  int count_v;
  Matrix matrix3d;
  vector<polygon_t> polygons;
  vector<double> array_for_vertices;
  vector<int> array_for_facets;
  double max;
  double min;
} data_t;
}  // namespace s21

#endif