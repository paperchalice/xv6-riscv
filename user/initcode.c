
#include "kernel/syscall.h"

char init[] = "/init";
char *argv[] = {init, nullptr};

[[noreturn, gnu::naked]] static void start_exec(char *init, char *argv[]) {
  asm("li a7, %0\n\t"
      "ecall\n\t"
      :
      : "i"(SYS_exit));
}

[[gnu::naked]] void start() {
  start_exec(init, argv);
  for (;;) {
    asm("li a7, %0\n\t"
        "ecall\n\t"
        :
        : "i"(SYS_exit));
  }
}
