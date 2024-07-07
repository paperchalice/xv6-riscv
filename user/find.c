// clang-format off
#include "kernel/types.h"
// clang-format on
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

#define BUF_LEN 256

int end_with(const char *str, const char *pattern) {
  uint str_len = strlen(str);
  uint pattern_len = strlen(pattern);
  if (str_len < pattern_len)
    return 0;
  if (str_len == pattern_len)
    return strcmp(str, pattern) == 0;

  uint start = str_len - pattern_len;
  if (strcmp(str + start, pattern) == 0)
    return str[start - 1] == '/';
  return 0;
}

static int find(const char *pwd, int fd, const char *name) {

  struct dirent de = {0};
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;
    if (end_with(de.name, name))
      printf("%s/%s\n", pwd, de.name);

    struct stat st = {0};
    char cur_buf[BUF_LEN + 1] = {0};
    uint pwd_len = strlen(pwd);
    memmove(cur_buf, pwd, pwd_len);
    cur_buf[pwd_len] = '/';
    memmove(cur_buf + pwd_len + 1, de.name, strlen(de.name));

    int cur_fd = open(cur_buf, O_RDONLY);
    if (cur_fd < 0) {
      fprintf(2, "find: cannot open file %s\n", cur_buf);
      close(cur_fd);
      return 1;
    }
    if (fstat(cur_fd, &st) < 0) {
      fprintf(2, "find: cannot stat %s\n", de.name);
      close(cur_fd);
      return 1;
    }
    if (st.type == T_DIR)
      find(cur_buf, cur_fd, name);
    close(cur_fd);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(2, "Usage: find <dir> <filename>\n");
    exit(1);
  }

  const char *dir = argv[1];
  const char *filename = argv[2];

  int fd = 0;
  if ((fd = open(dir, O_RDONLY)) < 0) {
    fprintf(2, "find: cannot open directory %s\n", dir);
    exit(1);
  }

  int err = find(dir, fd, filename);
  return err;
}
