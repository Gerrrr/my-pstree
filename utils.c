#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>

#include "process.h"
#include "utils.h"

void trim (char *s) {
  int n = strlen(s)-1;
  if ((n > 0) && (s[n] == '\n')) {
    s[n] = '\0';
  }
}

bool starts_with(const char *a, const char *b) {
   // from http://stackoverflow.com/questions/15515088/how-to-check-if-string-starts-with-certain-string-in-c
   if (strncmp(a, b, strlen(b)) == 0) {
     return 1;
   }
   return 0;
}

int get_max_proc(int* res) {
  /*
  Reads pid_max and returns the maximum process count

  res: pointer to integer to store the result
  */
  const int buf_size = 100;
  char buf[buf_size];
  char pid_max_path[] = "/proc/sys/kernel/pid_max";
  char error_msg[buf_size];

  FILE *fp = fopen(pid_max_path, "r");
  if (!fp){
    perror("Couldn't open /proc/sys/kernel/pid_max");
    return 1;
  }

  if (!fgets(buf, buf_size, fp)){
    perror("Couldn't read from /proc/sys/kernel/pid_max");
    return 1;
  }

  fclose(fp);
  *res = atoi(buf);
  if (*res < 1) {
    sprintf(error_msg, "Error while parsing pid_max: %d", *res);
    perror(error_msg);
  }
  return 0;
}

int is_proc_dir(const struct dirent *d) {
  /*
  Predicate function to check if the passed directory contains process information
  */
  const bool is_dir = (d->d_type == DT_DIR);
  const bool only_digits = (atoi(d->d_name) != 0);
  return is_dir && only_digits;
}

int numsort(const struct dirent ** d1, const struct dirent ** d2) {
  const int n1 = atoi((*d1)->d_name);
  const int n2 = atoi((*d2)->d_name);
  if (n1 < n2) {
    return -1;
  }
  else if(n1 > n2) {
    return 1;
  }
  else {
    return 0;
  }
}
