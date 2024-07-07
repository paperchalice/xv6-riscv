#ifndef XV6_KERNEL_SYSINFO_H
#define XV6_KERNEL_SYSINFO_H

#include <stdint.h>

struct sysinfo {
  uint64_t freemem; // amount of free memory (bytes)
  uint64_t nproc;   // number of process
};

#endif // XV6_KERNEL_SYSINFO_H
