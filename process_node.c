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

  ProcessNodeLinkedList_t *current = create_process_node_ll(node);
  ProcessNodeLinkedList_t *last = current;
  ProcessNodeLinkedList_t *intermediate;
  ProcessNode_t *current_node = node;
  while(current) {
    current_node = current->node;
    if(current_node->process) {
      destroy_process(current_node->process);
      current_node->process = NULL;
    }

    if(current_node->next_node) {
      last = add_process_node_to_ll(last, current_node->next_node);
      current_node->next_node = NULL;
    }

    if(current_node->child) {
      last = add_process_node_to_ll(last, current_node->child);
      node->child = NULL;
    }

    free(current_node);
    intermediate = current->next;
    current->node = NULL;
    current->next = NULL;
    free(current);
    current = intermediate;
    intermediate = NULL;
  }
}

ProcessNodeLinkedList_t *create_process_node_ll(ProcessNode_t *node) {
  ProcessNodeLinkedList_t *list = malloc(sizeof(ProcessNodeLinkedList_t));
  list->node = node;
  list->next = NULL;
  return list;
}

ProcessNodeLinkedList_t *add_process_node_to_ll(
  ProcessNodeLinkedList_t *current, ProcessNode_t *node) {
  ProcessNodeLinkedList_t *el = create_process_node_ll(node);
  ProcessNodeLinkedList_t *last = current;
  while(last->next != NULL) {
    last = last->next;
  }
  last->next = el;
  return el;
}
