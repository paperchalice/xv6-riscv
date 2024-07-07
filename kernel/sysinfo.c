// clang-format off
#include "types.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"
// clang-format on
#include "sysinfo.h"
#include "param.h"
#include "proc.h"

uint64_t collect_freemem();
uint64_t collect_nproc();

uint64_t sys_sysinfo(void) {
  uint64_t pinfo; // user pointer to struct sysinfo
  struct sysinfo info = {
      .freemem = collect_freemem(),
      .nproc = collect_nproc(),
  };

  argaddr(0, &pinfo);
  struct proc *p = myproc();
  if (copyout(p->pagetable, pinfo, (char *)&info, sizeof(struct sysinfo)) < 0)
    return -1;
  return 0;
}
