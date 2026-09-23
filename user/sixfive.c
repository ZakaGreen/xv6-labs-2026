#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

static int
is_delimiter(char c)
{
  return strchr(" -\r\t\n./,", c) != 0;
}

char buf[512];

enum state {
  DELIM,
  DIGIT,
  OTHER
};

static int
get_char_type(char c)
{
  if (c >= '0' && c <= '9')
    return DIGIT;

  if (is_delimiter(c))
    return DELIM;

  return OTHER;
}

static void
print_number(int value)
{
  if (value % 5 == 0 || value % 6 == 0)
    printf("%d\n", value);
}

void
sixfive(int fd)
{
  int n, i;
  int state = DELIM;
  int value = 0;

  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    for (i = 0; i < n; i++) {
      char c = buf[i];
      int type = get_char_type(c);

      if (state == DELIM) {
        if (type == DIGIT) {
          value = c - '0';
          state = DIGIT;
        } else if (type == OTHER) {
          state = OTHER;
        }

      } else if (state == DIGIT) {
        if (type == DIGIT) {
          value = value * 10 + (c - '0');

        } else if (type == DELIM) {
          print_number(value);
          value = 0;
          state = DELIM;

        } else {
          value = 0;
          state = OTHER;
        }

      } else {
        if (type == DELIM)
          state = DELIM;
      }
    }
  }

  if (n < 0) {
    fprintf(2, "sixfive: read error\n");
    exit(1);
  }

  if (state == DIGIT)
    print_number(value);
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if (argc <= 1) {
    sixfive(0);
    exit(0);
  }

  for (i = 1; i < argc; i++) {
    if ((fd = open(argv[i], O_RDONLY)) < 0) {
      fprintf(2, "sixfive: cannot open %s\n", argv[i]);
      exit(1);
    }

    sixfive(fd);
    close(fd);
  }

  exit(0);
}