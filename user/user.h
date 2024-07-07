#include "sys/types.h"
struct stat;

// system calls

#define SYSCALL(ATTR, NAME, RET, ARGS) ATTR RET NAME ARGS;
#include "kernel/syscall.def"

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...);
void printf(const char*, ...);
char* gets(char*, int max);
uint_t strlen(const char *);
void *memset(void *, int, uint_t);
void *malloc(uint_t);
void free(void*);
int atoi(const char*);
int memcmp(const void *, const void *, uint_t);
void *memcpy(void *, const void *, uint_t);
