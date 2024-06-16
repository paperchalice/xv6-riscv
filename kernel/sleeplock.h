// Long-term locks for processes

#ifndef XV6_KERNEL_SLEEPLOCK_H
#define XV6_KERNEL_SLEEPLOCK_H

struct sleeplock {
  uint_t locked;      // Is the lock held?
  struct spinlock lk; // spinlock protecting this sleep lock
  
  // For debugging:
  char *name;        // Name of lock.
  int pid;           // Process holding lock
};

#endif // XV6_KERNEL_SLEEPLOCK_H
