#include "sys/types.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p[2] = {0, 0};
  pipe(p);

  if (fork() == 0) {
    // Read from pipe.
    char c = 0;
    if (read(p[0], &c, 1))
      printf("%d: received ping\n", getpid());
    write(p[1], &c, 1);
  } else {
    // Send a byte to children.
    char c = 'A';
    write(p[1], &c, 1);
    if (read(p[0], &c, 1))
      printf("%d: received pong\n", getpid());
  }

  return 0;
}
