#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

void memdump(char* fmt, char* data, int len);

static uint16 read_u16(char* p) {
  uint8* b = (uint8*)p;
  return (uint16)b[0] | ((uint16)b[1] << 8);
}

static uint32 read_u32(char* p) {
  uint8* b = (uint8*)p;
  return (uint32)b[0] |
         ((uint32)b[1] << 8) |
         ((uint32)b[2] << 16) |
         ((uint32)b[3] << 24);
}

static uint64 read_u64(char* p) {
  uint8* b = (uint8*)p;
  return (uint64)b[0] |
         ((uint64)b[1] << 8) |
         ((uint64)b[2] << 16) |
         ((uint64)b[3] << 24) |
         ((uint64)b[4] << 32) |
         ((uint64)b[5] << 40) |
         ((uint64)b[6] << 48) |
         ((uint64)b[7] << 56);
}

static void print_hex64(uint64 value) {
  char digits[] = "0123456789abcdef";
  char buf[16];
  int n = 0;

  if (value == 0) {
    printf("0\n");
    return;
  }

  while (value != 0) {
    buf[n++] = digits[value & 0xf];
    value >>= 4;
  }

  while (n > 0) {
    printf("%c", buf[--n]);
  }

  printf("\n");
}

void memdump(char* fmt, char* data, int len) {
  int pos = 0;
  int i;

  for (i = 0; fmt[i] != 0; i++) {
    char c = fmt[i];
    int need;

    switch (c) {
      case 'i':
        need = 4;

        if (pos + need > len) {
          printf("memdump: not enough data for '%c'\n", c);
          return;
        }

        printf("%d\n", (int)read_u32(data + pos));
        pos += need;
        break;

      case 'p':
        need = 8;

        if (pos + need > len) {
          printf("memdump: not enough data for '%c'\n", c);
          return;
        }

        print_hex64(read_u64(data + pos));
        pos += need;
        break;

      case 'h':
        need = 2;

        if (pos + need > len) {
          printf("memdump: not enough data for '%c'\n", c);
          return;
        }

        printf("%d\n", (short)read_u16(data + pos));
        pos += need;
        break;

      case 'c':
        need = 1;

        if (pos + need > len) {
          printf("memdump: not enough data for '%c'\n", c);
          return;
        }

        printf("%c\n", data[pos]);
        pos += need;
        break;

      case 's': {
        need = 8;

        if (pos + need > len) {
          printf("memdump: not enough data for '%c'\n", c);
          return;
        }

        uint64 address = read_u64(data + pos);
        char* ptr = (char*)address;

        if (ptr != 0)
          printf("%s\n", ptr);
        else
          printf("(null)\n");

        pos += need;
        break;
      }

      case 'S': {
        int j = pos;

        while (j < len && data[j] != 0)
          j++;

        write(1, data + pos, j - pos);
        write(1, "\n", 1);

        if (j < len)
          pos = j + 1;
        else
          pos = len;

        break;
      }

      default:
        printf("memdump: unknown format '%c'\n", c);
        return;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Example 1:\n");
    int a[2] = {61810, 2026};
    memdump("ii", (char*)a, sizeof(a));

    printf("Example 2:\n");
    memdump("S", "a string", sizeof("a string"));

    printf("Example 3:\n");
    char* s = "another";
    memdump("s", (char*)&s, sizeof(s));

    struct sss {
      char* ptr;
      int num1;
      short num2;
      char byte;
      char bytes[8];
    } example;

    example.ptr = "hello";
    example.num1 = 1819438967;
    example.num2 = 100;
    example.byte = 'z';
    strcpy(example.bytes, "xyzzy");

    printf("Example 4:\n");
    memdump("pihcS", (char*)&example, sizeof(example));

    printf("Example 5:\n");
    memdump("sccccc", (char*)&example, sizeof(example));

  } else if (argc == 2) {
    char data[512];
    int n = 0;

    memset(data, '\0', sizeof(data));

    while (n < sizeof(data)) {
      int nn = read(0, data + n, sizeof(data) - n);

      if (nn <= 0)
        break;

      n += nn;
    }

    memdump(argv[1], data, n);

  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }

  exit(0);
}