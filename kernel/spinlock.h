// Mutual exclusion lock.

#ifndef XV6_KERNEL_SPINLOCK_H
#define XV6_KERNEL_SPINLOCK_H

struct spinlock {
  uint_t locked; // Is the lock held?

  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
};

#endif // XV6_KERNEL_SPINLOCK_H
