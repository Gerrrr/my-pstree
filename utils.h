#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <dirent.h>

#include "process.h"

void trim (char *s);
bool starts_with(const char *a, const char *b);
void insertion_sort(Process_t **arr, int length);
int get_max_proc();
int is_proc_dir(const struct dirent *d);
int numsort(const struct dirent ** d1, const struct dirent ** d2);

#endif
