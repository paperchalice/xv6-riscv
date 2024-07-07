#include "kernel/syscall.h"

#define SYSCALL(ATTR, NAME, RET, ARGS)                                         \
  [[gnu::naked]] void NAME() {                                                 \
    asm("li a7, %0\n\t"                                                        \
        "ecall\n\t"                                                            \
        "ret" ::"i"(SYS_##NAME));                                              \
  }
#include "kernel/syscall.def"
