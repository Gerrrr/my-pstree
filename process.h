#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process {
  int pid;
  char* name;
  int ppid;
} Process_t;

Process_t *create_process(char* pid);
void destroy_process(Process_t *p);
void print_process(Process_t *p, int num_indents);

#endif
