#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
  int pid;
  char* name;
  int ppid;
} Process_t;

int create_process(char* pid, Process_t **process);
void destroy_process(Process_t *p);
void print_process(Process_t *p, int num_indents);

#endif
