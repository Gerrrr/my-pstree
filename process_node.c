#include <stdlib.h>
#include <assert.h>

#include "process_node.h"


ProcessNode_t *create_process_node(Process_t *process) {
  ProcessNode_t *process_node = malloc(sizeof(ProcessNode_t));
  process_node->process = process;
  process_node->child = NULL;
  process_node->next_node = NULL;
  return process_node;
}

void print_process_node(ProcessNode_t *node, int indent) {
  ProcessNode_t *current_node = node;
  while(current_node) {
    print_process(current_node->process, indent);
    if(current_node->child) {
      print_process_node(current_node->child, indent + 2);
    }
    current_node = current_node->next_node;
  }
}

void destroy_process_node(ProcessNode_t *node) {
  assert(node != NULL);
  if(node->process) {
    destroy_process(node->process);
    node->process = NULL;
  }

  if(node->next_node) {
    destroy_process_node(node->next_node);
    node->next_node = NULL;
  }

  if(node->child) {
    destroy_process_node(node->child);
    node->child = NULL;
  }

  free(node);
}
