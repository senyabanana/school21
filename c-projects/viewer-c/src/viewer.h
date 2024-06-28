#ifndef _SRC_VIEWER_H_
#define _SRC_VIEWER_H_

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#define PI 3.14159265358979323846

typedef struct facets {
  int *vertices;
  int numbers_of_vertices_in_facets;
} polygon_t;

typedef struct Object3D {
  int count_of_vertices;
  int count_of_facets;
  int count_v;
  matrix_t matrix3d;
  polygon_t *polygons;
  double *array_for_vertices;
  int *array_for_facets;
  double max;
  double min;
} object_t;

int process_input_data(object_t *data, char *file_name);
void process_vertices(object_t *data, FILE *file);
void process_facets(object_t *data, FILE *file);
void vertices_to_array(object_t *data);
void facets_to_array(object_t *data);

#endif