// System call numbers

#ifndef XV6_KERNEL_SYSCALL_H
#define XV6_KERNEL_SYSCALL_H

enum {
  SYS_ = 0,
#define SYSCALL(ATTR, NAME, RET, ARGS) SYS_##NAME,
#include "kernel/syscall.def"
};

#endif // XV6_KERNEL_SYSCALL_H
