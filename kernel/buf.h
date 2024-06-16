#ifndef XV6_KERNEL_BUF_H
#define XV6_KERNEL_BUF_H

struct buf {
  int valid;   // has data been read from disk?
  int disk;    // does disk "own" buf?
  uint_t dev;
  uint_t blockno;
  struct sleeplock lock;
  uint_t refcnt;
  struct buf *prev; // LRU cache list
  struct buf *next;
  uchar_t data[BSIZE];
};

#endif // XV6_KERNEL_BUF_H
