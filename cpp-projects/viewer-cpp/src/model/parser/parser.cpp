#include "parser.h"

using namespace s21;

int Parser::processInputData(string& fileName) {
  setlocale(LC_NUMERIC, "C");
  ifstream file(fileName);
  if (!file.is_open()) {
    return -1;
  }
  data_.count_of_vertices = 0;
  data_.count_of_facets = 0;
  string line;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      data_.count_of_vertices++;
    }
    if (line[0] == 'f' && line[1] == ' ') {
      data_.count_of_facets++;
    }
  }
  file.clear();
  file.seekg(0, std::ios::beg);
  data_.matrix3d = Matrix(data_.count_of_vertices + 1, 3);
  data_.polygons.resize(data_.count_of_facets + 1);
  data_.count_v = 0;
  processVertices(file);
  file.clear();
  file.seekg(0, std::ios::beg);
  processFacets(file);
  file.close();
  return 0;
}

void Parser::processVertices(ifstream& file) {
  string line;
  int rows_vertex = 0;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      rows_vertex++;
      for (unsigned long i = 2, columns_vertex = 0; i < line.size();
           i++, columns_vertex++) {
        if (strchr("-1234567890", line[i])) {
          data_.matrix3d(rows_vertex, columns_vertex) =
              std::stod(line.substr(i));
          for (int skip = i; strchr("-1234567890.", line[skip]); skip++, i++) {
            continue;
          }
        }
      }
    }
  }
}

void Parser::processFacets(std::ifstream& file) {
  string line;
  int count_f = 0;
  while (std::getline(file, line)) {
    if (line[0] == 'f' && line[1] == ' ') {
      count_f++;
      for (unsigned long i = 2; i < line.size(); i++) {
        if (strchr("1234567890", line[i]) && strchr(" ", line[i - 1])) {
          data_.polygons[count_f].numbers_of_vertices_in_facets++;
          data_.count_v++;
        }
      }
      data_.polygons[count_f].vertices =
          vector<int>(data_.polygons[count_f].numbers_of_vertices_in_facets);
      for (unsigned long i = 2, columns_facet = 0; i < line.size(); i++) {
        if (strchr("1234567890", line[i]) && strchr(" ", line[i - 1])) {
          data_.polygons[count_f].vertices[columns_facet] =
              std::stod(line.substr(i));
          columns_facet++;
        }
      }
    }
  }
}

void Parser::verticesToArray() {
  data_.max = 0;
  data_.min = 0;
  data_.array_for_vertices.clear();
  data_.array_for_vertices.reserve(3 * (data_.count_of_vertices + 1));
  int index = 0;
  for (int i = 0; i <= data_.count_of_vertices; i++) {
    for (int j = 0; j < 3; j++, index++) {
      data_.array_for_vertices.push_back(data_.matrix3d(i, j));
      if (data_.array_for_vertices[index] < data_.min) {
        data_.min = data_.array_for_vertices[index] * 2;
      }
      if (data_.array_for_vertices[index] > data_.max) {
        data_.max = data_.array_for_vertices[index] * 2;
      }
    }
  }
  if (fabs(data_.min) > fabs(data_.max)) {
    data_.max = fabs(data_.min);
  } else {
    data_.min = -fabs(data_.max);
  }
}

void Parser::facetsToArray() {
  data_.array_for_facets.clear();
  data_.array_for_facets.reserve(data_.count_v * 2);
  int index = 0;
  for (int count_f = 1; count_f <= data_.count_of_facets; count_f++, index++) {
    for (int count_v = 0;
         count_v < data_.polygons[count_f].numbers_of_vertices_in_facets;
         count_v++, index++) {
      data_.array_for_facets.push_back(
          data_.polygons[count_f].vertices[count_v]);
      if (count_v != 0) {
        index++;
        data_.array_for_facets.push_back(data_.array_for_facets[index - 1]);
      }
    }
    data_.array_for_facets.push_back(data_.polygons[count_f].vertices[0]);
  }
  data_.polygons.clear();
}

void Parser::printMatrix() {
  for (int i = 0; i < data_.matrix3d.getRows(); ++i) {
    std::cout << "Vetrex " << i << ": ";
    for (int j = 0; j < data_.matrix3d.getColumns(); ++j) {
      std::cout << data_.matrix3d(i, j) << "\t";
    }
    std::cout << std::endl;
  }
}

void Parser::printPolygons() {
  for (int i = 0; i < data_.count_of_facets + 1; ++i) {
    std::cout << "Polygon " << i << ": ";
    for (int j = 0; j < data_.polygons[i].numbers_of_vertices_in_facets; ++j) {
      std::cout << data_.polygons[i].vertices[j] << " ";
    }
    std::cout << std::endl;
  }
}
