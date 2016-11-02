#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#include "utils.h"
#include "process.h"
#include "process_node.h"


int main() {
  const char proc_path[] = "/proc";
  struct dirent **name_list;
  int i, dir_count;
  const int max_proc = get_max_proc();

  dir_count = scandir(proc_path, &name_list, is_proc_dir, numsort);
  if (dir_count < 0) {
        perror("scandir failed"); // TODO: more detailed error description
  }

  ProcessNode_t *root_node = create_process_node(NULL);
  ProcessNode_t *current_node;
  Process_t *process;
  ProcessNode_t **node_array = malloc(sizeof(ProcessNode_t) * max_proc);
  ProcessNode_t *parent_node;
  node_array[0] = root_node;

  for(i = 0; i < dir_count; i++) {
    process = create_process(name_list[i]->d_name);
    current_node = create_process_node(process);
    node_array[process->pid] = current_node;

    parent_node = node_array[process->ppid];
    if(parent_node->child) {
      current_node->next_node = parent_node->child;
      parent_node->child = current_node;
    }
    else {
      parent_node->child = current_node;
    }
    free(name_list[i]);
  }
  free(name_list);

  print_process_node(root_node->child, 0);
  destroy_process_node(root_node);
  for(i = 0; i < max_proc; i++) {
    // all the process nodes are already freed by destroy_process_node
    node_array[i] = NULL;
  }
  free(node_array);
  return 0;
}