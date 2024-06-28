#include "viewer.h"

int process_input_data(object_t *data, char *file_name) {
  setlocale(LC_NUMERIC, "C");
  FILE *file;
  file = fopen(file_name, "r+");
  if (!file) {
    return -1;
  }
  data->count_of_vertices = 0;
  data->count_of_facets = 0;
  char str[1025] = "";
  while (fgets(str, 1024, file) != NULL) {
    if (str[0] == 'v' && str[1] == ' ') {
      data->count_of_vertices++;
    }
    if (str[0] == 'f' && str[1] == ' ') {
      data->count_of_facets++;
    }
  }
  fseek(file, 0, SEEK_SET);
  create_matrix(data->count_of_vertices + 1, 3, &data->matrix3d);
  data->polygons = calloc(data->count_of_facets + 1, sizeof(polygon_t));
  data->count_v = 0;
  process_vertices(data, file);
  fseek(file, 0, SEEK_SET);
  process_facets(data, file);
  fclose(file);
  return 0;
}

void process_vertices(object_t *data, FILE *file) {
  char str[1025] = "";
  int rows_vertex = 0;
  while (fgets(str, 1024, file) != NULL) {
    if (str[0] == 'v' && str[1] == ' ') {
      rows_vertex++;
      for (int i = 2, columns_vertex = 0; str[i] != '\0';
           i++, columns_vertex++) {
        if (strchr("-1234567890", str[i])) {
          data->matrix3d.matrix[rows_vertex][columns_vertex] = atof(str + i);
          for (int skip = i; strchr("-1234567890.", str[skip]); skip++, i++) {
            continue;
          }
        }
      }
    }
  }
}

void process_facets(object_t *data, FILE *file) {
  char str[1025] = "";
  int count_f = 0;
  while (fgets(str, 1024, file) != NULL) {
    if (str[0] == 'f' && str[1] == ' ') {
      count_f++;
      for (int i = 2; str[i] != '\0'; i++) {
        if (strchr("1234567890", str[i]) && strchr(" ", str[i - 1])) {
          data->polygons[count_f].numbers_of_vertices_in_facets++;
          data->count_v++;
        }
      }
      data->polygons[count_f].vertices = calloc(
          data->polygons[count_f].numbers_of_vertices_in_facets, sizeof(int));
      for (int i = 2, columns_facet = 0; str[i] != '\0'; i++) {
        if (strchr("1234567890", str[i]) && strchr(" ", str[i - 1])) {
          data->polygons[count_f].vertices[columns_facet] = atoi(str + i);
          columns_facet++;
        }
      }
    }
  }
}

void vertices_to_array(object_t *data) {
  data->max = 0;
  data->min = 0;
  data->array_for_vertices =
      calloc(sizeof(double), (data->count_of_vertices + 1) * 3);
  int index = 0;
  for (int i = 0; i <= data->count_of_vertices; i++) {
    for (int j = 0; j < 3; j++, index++) {
      data->array_for_vertices[index] = data->matrix3d.matrix[i][j];
      if (data->array_for_vertices[index] < data->min) {
        data->min = data->array_for_vertices[index] * 2;
      }
      if (data->array_for_vertices[index] > data->max) {
        data->max = data->array_for_vertices[index] * 2;
      }
    }
  }
  if (fabs(data->min) > fabs(data->max)) {
    data->max = fabs(data->min);
  } else {
    data->min = -fabs(data->max);
  }
  remove_matrix(&data->matrix3d);
}

void facets_to_array(object_t *data) {
  data->array_for_facets = calloc(sizeof(int), data->count_v * 2);
  int index = 0;
  for (int count_f = 1; count_f <= data->count_of_facets; count_f++, index++) {
    for (int count_v = 0;
         count_v < data->polygons[count_f].numbers_of_vertices_in_facets;
         count_v++, index++) {
      data->array_for_facets[index] = data->polygons[count_f].vertices[count_v];
      if (count_v != 0) {
        index++;
        data->array_for_facets[index] = data->array_for_facets[index - 1];
      }
    }
    data->array_for_facets[index] = data->polygons[count_f].vertices[0];
  }
  for (int i = 0; i < data->count_of_facets + 1; i++) {
    free(data->polygons[i].vertices);
  }
  free(data->polygons);
}