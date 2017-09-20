
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "tree.h"
#include "list.h"
#include "db.h"

void exit_program()
{
  return;
}

int main (void)
{
  tree_t *tree = tree_new();
  //item_t item = make_item("hej", 1, 1, "A25");
  //tree_insert(tree, "test", item);
  free(tree);
  return 0;
}
