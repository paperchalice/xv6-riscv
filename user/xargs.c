// clang-format off
#include "kernel/types.h"
// clang-format on
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(2, "Usage: xargs <command> [args]...");
  }

  char *child_argv[MAXARG] = {0};
  int i = 1;
  for (; i != argc; ++i)
    child_argv[i - 1] = argv[i];

  i -= 1;

  {
    char buf[128] = {0};
    int j = 0;
    char c = 0;
    child_argv[i] = buf;

    while (read(0, &c, 1) == 1) {
      if (c != '\n') {
        buf[j++] = c;
        continue;
      }
      if (fork() == 0)
        exec(argv[1], child_argv);
      wait(0);
      memset(buf, 0, j);
      j = 0;
    }
  }

  return 0;
}
