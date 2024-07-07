#include "kernel/types.h"
#include "user/user.h"

static void output(int r) {
  int prime = 0;
  read(r, &prime, sizeof(int));
  if (prime)
    printf("prime %d\n", prime);
  else
    return;

  // Set up a new pipe.
  int p[2] = {0};
  pipe(p);

  int in = 0;
  while (read(r, &in, sizeof(int)))
    if (in % prime)
      write(p[1], &in, sizeof(int));
  close(p[1]);
  close(r);

  if (fork() == 0) {
    output(p[0]);
  }
}

// If the read side of a pipe is closed after `read` is called, `read` is still
// blocked. So we write pipe firstly.
int main(int, char *[]) {
  // Set up init pipe.
  int p[2] = {0};
  pipe(p);

  for (int i = 2; i != 36; ++i)
    write(p[1], &i, sizeof(int));
  close(p[1]);

  if (fork() == 0) {
    output(p[0]);
  }

  wait(0); // Wait all children.

  return 0;
}
