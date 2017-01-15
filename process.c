#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <errno.h>

#include "utils.h"
#include "process.h"

#define BUF_SIZE 100

int create_process(char *pid, Process_t **process) {
  /*
  pid: pid of the process whose information is to be read
  process: pointer to the process to be created

  returns: 0 upon successfull execution and 1 otherwise
  */

  const char status_path_template[] = "/proc/%s/status";
  const int status_path_template_len = strlen(status_path_template) + 1;
  const int pid_len = strlen(pid);
  const int status_path_len = status_path_template_len + pid_len - 2;

  char status_path[status_path_len];
  char error_msg[BUF_SIZE];

  Process_t *p = (Process_t *)malloc(sizeof(Process_t));
  assert(p != NULL);
  p->pid = atoi(pid);

  sprintf(status_path, status_path_template, pid);

  // check that the process status file accessible
  struct stat sb;
  if (stat(status_path, &sb) == -1) {
    sprintf(error_msg, "stat error: %s", status_path);
    perror(error_msg);
    return 1;
  }

  FILE *fp = fopen(status_path, "r");
  if (fp == NULL){
    sprintf(error_msg, "Couldn't open %s", status_path);
    perror(error_msg);
    return 1;
  }

  char buf[BUF_SIZE];
  int delimiter_len;
  char *substring;

  // parse name and ppid from the status file
  while(fgets(buf, BUF_SIZE, fp) != NULL) {
    trim(buf);
    if (starts_with(buf, "Name:")) {
      char delimiter[] = "Name:\t";
      delimiter_len = strlen(delimiter);
      substring = strstr(buf, delimiter);
      p->name = (char *) malloc(strlen(substring) - delimiter_len + 1);
      assert(p->name != NULL);
      strcpy(p->name, substring + delimiter_len);
    }
    else if(starts_with(buf, "PPid:")) {
      char delimiter[] = "PPid:\t";
      delimiter_len = strlen(delimiter);
      substring = strstr(buf, delimiter);
      p->ppid = atoi(substring + delimiter_len);
    }
  }

  if (fclose(fp) != 0) {
    sprintf(error_msg, "fclose failed: %s", strerror(errno));
    perror(error_msg);
    return 1;
  }
  *process = p;
  return 0;
}

void destroy_process(Process_t *p)
{
    assert(p != NULL);
    if(p->name) {
      free(p->name);
      p->name = NULL;
    }
    free(p);
}

void print_process(Process_t *p, int num_indents) {
  int i = 0;
  printf("|");
  for(i = 0; i < num_indents; i++) {
    printf("—");
  }
  printf("→[%d %s]\n", p->pid, p->name);
}
