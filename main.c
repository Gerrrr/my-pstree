#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "utils.h"
#include "process.h"
#include "process_node.h"


int main() {
  const char proc_path[] = "/proc";
  struct dirent **name_list;
  int i;
  int dir_count;
  int err;
  int max_proc;

  err = get_max_proc(&max_proc);
  if (err) {
    printf("Error while obtaining max_proc\n");
    return 1;
  }


  dir_count = scandir(proc_path, &name_list, is_proc_dir, numsort);
  if (dir_count < 0) {
        perror("scandir failed"); // TODO: more detailed error description
        return 1;
  }
  ProcessNode_t *root_node = create_process_node(NULL);
  ProcessNode_t *current_node = NULL;
  Process_t *process = NULL;
  ProcessNode_t **node_array = malloc(sizeof(ProcessNode_t) * max_proc);
  ProcessNode_t *parent_node = NULL;
  node_array[0] = root_node;

  for(i = 0; i < dir_count; i++) {
    err = create_process(name_list[i]->d_name, &process);
    if(err) {
      return 1;
    }
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
    process = NULL;
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
