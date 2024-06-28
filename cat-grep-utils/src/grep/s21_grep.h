#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERRMSG "Ошибка: неверные параметры командной строки\n"
#define MAX_GROUPS 10

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int error;
  char *regex;
  char *file;
  regex_t re;
  int line_num;
  int line_count;
  int multiple_files;
} options;

void get_options(int argc, char *argv[], options *opts);
void process_data_files(options *opts, char *argv[], int argc, int optind);
void process_f_flag(char *progname, options *opts, char *optarg);
void process_options(options *opts, int argc, int *optind, char *argv[]);
void process_line(char *line, options *opts);
void file_grep(char *filepath, options *opts);
void regex_cat(char **regex_string, char *regex);
int regex_compile(options *opts);
void line_print(char *line, options *opts, int offset, int length);
void regex_file_parse(options *opts, char *filepath);
void remove_endline(char *str);
void graceful_exit(options *opts);

#endif