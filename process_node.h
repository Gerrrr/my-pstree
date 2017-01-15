#include "process.h"

typedef struct ProcessNode {
  Process_t *process;
  struct ProcessNode *next_node;
  struct ProcessNode *child;
} ProcessNode_t;

ProcessNode_t *create_process_node(Process_t *process);
void print_process_node(ProcessNode_t *node, int indent);
void destroy_process_node(ProcessNode_t *node);

typedef struct ProcessNodeLinkedList {
  ProcessNode_t *node;
  struct ProcessNodeLinkedList *next;
} ProcessNodeLinkedList_t;

ProcessNodeLinkedList_t *create_process_node_ll(ProcessNode_t *node);
ProcessNodeLinkedList_t *add_process_node_to_ll(
  ProcessNodeLinkedList_t *current,
  ProcessNode_t *node);
