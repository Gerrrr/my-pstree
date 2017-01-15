#ifndef PROCESS_NODE_H
#define PROCESS_NODE_H

#include "process.h"

typedef struct ProcessNode {
  Process_t *process;
  struct ProcessNode *next_node;
  struct ProcessNode *child;
} ProcessNode_t;

ProcessNode_t *create_process_node(Process_t *process);
void print_process_node(ProcessNode_t *node, int indent);
void destroy_process_node(ProcessNode_t *node);

#endif
