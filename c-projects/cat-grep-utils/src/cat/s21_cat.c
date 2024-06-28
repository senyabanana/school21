#include "s21_cat.h"

void get_options(int argc, char *argv[], options *opts) {
  int opt;
  opts->line = 0;
  opts->gobble = 0;
  opts->prev = '\n';
  int options_index;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "benstvTE", long_options,
                            &options_index)) != -1) {
    switch (opt) {
      case 'b':
        opts->b = opts->n = 1;
        break;
      case 'e':
        opts->e = opts->v = 1;
        break;
      case 'n':
        opts->n = 1;
        break;
      case 's':
        opts->s = 1;
        break;
      case 't':
        opts->t = opts->v = 1;
        break;
      case 'v':
        opts->v = 1;
        break;
      case 'T':
        opts->t = 1;
        break;
      case 'E':
        opts->e = 1;
        break;
      default:
        printf("usage: cat [-benstvTE] [file ...]\n");
        exit(1);
    }
  }
}

void get_files(int argc, char *argv[], char **files, int *count_files) {
  for (int i = optind; i < argc; i++) {
    files[*count_files] = argv[i];
    *count_files += 1;
  }
}

void raw_cat(FILE *fp) {
  int ch;
  while ((ch = getc(fp)) != EOF) {
    putchar(ch);
  }
  if (ferror(fp)) {
    perror("File read error");
  }
}

void cook_cat(options *opts, FILE *fp) {
  int ch;

  for (opts->prev = '\n'; (ch = getc(fp)) != EOF; opts->prev = ch) {
    if (opts->prev == '\n') {
      if (opts->s) {
        if (ch == '\n') {
          if (opts->gobble) continue;
          opts->gobble = 1;
        } else
          opts->gobble = 0;
      }
      if (opts->n && (!opts->b || ch != '\n')) {
        printf("%6d\t", ++(opts->line));
      }
    }
    if (ch == '\n') {
      if (opts->e && putchar('$') == EOF) break;
    } else if (ch == '\t') {
      if (opts->t) {
        if (putchar('^') == EOF || putchar('I') == EOF) break;
        continue;
      }
    } else if (opts->v) {
      if (!(ch >= 0 && ch < 128) && !(ch >= ' ' && ch <= '~')) {
        if (putchar('M') == EOF || putchar('-') == EOF) break;
        ch = (ch & 0x7F);
      }
      if ((ch >= 0 && ch < 32) || ch == 127) {
        if (putchar('^') == EOF ||
            putchar(ch == '\177' ? '?' : ch | 0100) == EOF)
          break;
        continue;
      }
    }
    if (putchar(ch) == EOF) break;
  }
  if (ferror(fp)) {
    perror("File read error");
  }
}

int main(int argc, char *argv[]) {
  options opts = {0};
  int count_files = 0;
  char *files[argc];
  get_options(argc, argv, &opts);
  get_files(argc, argv, files, &count_files);

  if (count_files == 0) {
    if (opts.b || opts.e || opts.n || opts.s || opts.t || opts.v)
      cook_cat(&opts, stdin);
    else
      raw_cat(stdin);
  } else {
    for (int i = 0; i < count_files; i++) {
      FILE *file = fopen(files[i], "r");
      if (!file) {
        perror(argv[i]);
      } else {
        if (opts.b || opts.e || opts.n || opts.s || opts.t || opts.v)
          cook_cat(&opts, file);
        else
          raw_cat(file);
        fclose(file);
      }
    }
  }

  return 0;
}