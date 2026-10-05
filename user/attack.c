#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"


#define DATASIZE (64 * 4096)
#define MSG "Here it is: "

int match(char* p, char* s) {
  while (*s) {
    if (*p != *s) return 0;
    p++;
    s++;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  char* data;
  char* p;
  char* end;
  int msglen;

  data = sbrk(DATASIZE);
  if (data == (char*)-1) {
    exit(1);
  }

  msglen = strlen(MSG);
  end = data + DATASIZE - msglen;

  for (p = data; p < end; p++) {
    if (match(p, MSG)) {
      printf("%s\n", p + msglen);
      exit(0);
    }
  }

  exit(1);
}