#include "s21_grep.h"

void get_options(int argc, char *argv[], options *opts) {
  int opt;
  opts->regex = NULL;
  opts->line_num = 1;

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        opts->e = 1;
        regex_cat(&opts->regex, optarg);
        break;
      case 'i':
        opts->i = 1;
        break;
      case 'v':
        opts->v = 1;
        break;
      case 'c':
        opts->c = 1;
        break;
      case 'l':
        opts->l = 1;
        break;
      case 'n':
        opts->n = 1;
        break;
      case 'h':
        opts->h = 1;
        break;
      case 's':
        opts->s = 1;
        break;
      case 'f':
        opts->f = 1;
        process_f_flag(argv[0], opts, optarg);
        break;
      case 'o':
        opts->o = 1;
        break;
      default:
        fprintf(stderr, ERRMSG);
        graceful_exit(opts);
        exit(EXIT_FAILURE);
    }
  }
}

void process_data_files(options *opts, char *argv[], int argc, int optind) {
  for (int i = optind; i < argc; i++) {
    if (access(argv[i], F_OK) != 0) {
      if (!opts->s)
        fprintf(stderr, "%s: %s: Файл или каталог не существует\n", argv[0],
                argv[i]);
      continue;
    }
    file_grep(argv[i], opts);
  }
}

void process_f_flag(char *progname, options *opts, char *optarg) {
  if (access(optarg, F_OK) != 0) {
    fprintf(stderr, "%s: %s: Файл или каталог не существует\n", progname,
            optarg);
    opts->error = 1;
  } else {
    regex_file_parse(opts, optarg);
  }
}

void process_options(options *opts, int argc, int *optind, char *argv[]) {
  if (opts->l) opts->c = opts->o = 0;

  if (opts->c) opts->o = 0;

  if (opts->v && opts->o) opts->error = 1;

  if (*optind + 1 - (opts->f || opts->e) >= argc) opts->error = 1;
  if (!opts->f && !opts->e && !opts->error)
    regex_cat(&opts->regex, argv[(*optind)++]);

  if ((argc - *optind) > 1) opts->multiple_files = 1;
  if (opts->regex) regex_compile(opts);
}

void process_line(char *line, options *opts) {
  int match = 0;

  int str_offset = 0;
  int str_len = 0;
  regmatch_t matches[MAX_GROUPS];
  do {
    match = !regexec(&opts->re, line, MAX_GROUPS, matches, 0);

    if (match != opts->v) opts->line_count++;

    if (opts->l || opts->c) continue;

    if (opts->o && match) {
      str_offset = matches[0].rm_so;
      str_len = matches[0].rm_eo - matches[0].rm_so;
    }

    if (opts->v) {
      if (!match) line_print(line, opts, str_offset, str_len);
    } else {
      if (match) line_print(line, opts, str_offset, str_len);
    }

    if (opts->o) line = line + matches[0].rm_eo;
  } while (opts->o && match);
}

void file_grep(char *filepath, options *opts) {
  char *line = NULL;
  size_t buf_len = 0;
  ssize_t line_len;
  FILE *file = fopen(filepath, "r");

  opts->file = filepath;

  while ((line_len = getline(&line, &buf_len, file)) != -1) {
    process_line(line, opts);

    if (opts->l && opts->line_count) {
      printf("%s\n", opts->file);
      break;
    }

    opts->line_num++;
  }

  if (opts->c) {
    (opts->multiple_files && !opts->h)
        ? printf("%s:%d\n", opts->file, opts->line_count)
        : printf("%d\n", opts->line_count);
  }

  opts->line_num = 1;
  opts->line_count = 0;

  free(line);
  fclose(file);
}

void regex_cat(char **regex_string, char *regex) {
  char *tmp = malloc(
      ((*regex_string ? strlen(*regex_string) + 2 : 0) + strlen(regex) + 1) *
      sizeof(char));

  sprintf(tmp, "%s%s%s", *regex_string ? *regex_string : "",
          *regex_string ? "\\|" : "", regex);

  *regex_string = realloc(*regex_string, strlen(tmp) + 1);

  strcpy(*regex_string, tmp);
  free(tmp);
}

int regex_compile(options *opts) {
  int reti = 0;

  reti =
      regcomp(&opts->re, opts->regex, (opts->i ? REG_ICASE : 0 | REG_NEWLINE));
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    opts->error = 1;
    return reti;
  }

  return 0;
}

void line_print(char *line, options *opts, int offset, int length) {
  if (opts->multiple_files && !opts->h) printf("%s:", opts->file);

  if (opts->n) printf("%d:", opts->line_num);

  (!offset && !length) ? printf("%s", line)
                       : printf("%.*s", (int)length, &line[offset]);
  if (opts->o == 1 || (line[strlen(line) - 1] -= '\n')) printf("\n");
}

void regex_file_parse(options *opts, char *filepath) {
  char *line = NULL;
  size_t buf_len = 0;
  ssize_t line_len;
  FILE *file = fopen(filepath, "r");

  while ((line_len = getline(&line, &buf_len, file)) != -1) {
    remove_endline(line);

    regex_cat(&opts->regex, line);
  }

  fclose(file);

  free(line);
}

void remove_endline(char *str) {
  if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
}

void graceful_exit(options *opts) {
  regfree(&opts->re);
  if (opts->regex) free(opts->regex);
}

int main(int argc, char *argv[]) {
  options opts = {0};
  opts.regex = NULL;
  opts.line_num = 1;

  get_options(argc, argv, &opts);
  process_options(&opts, argc, &optind, argv);
  if (!opts.error) process_data_files(&opts, argv, argc, optind);
  graceful_exit(&opts);
  (opts.error) ? exit(EXIT_FAILURE) : exit(EXIT_SUCCESS);
}
