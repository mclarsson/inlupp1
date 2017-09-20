
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

  char *keys[] = {"H", "D", "L", "B", "F", "J", "N", "A", "C", "E", "G", "I", "K", "M", "O"};
  int length = 15;

  // Test insertion
  for (int i = 0; i < length; ++i)
    {
      item_t *item = make_item("desc", 100);
      add_shelf(item, "F32", 10);
      if (tree_insert(tree, keys[i], item))
	{
	  printf("tree_insert: \t %s \n", keys[i]);
	}
    }

  // Test size
  printf("tree_size: \t %d \n", tree_size(tree));
  // Test depth
  printf("tree_depth: \t %d \n", tree_depth(tree));
  // Test key exists
  printf("tree_has_key: \t %d \t %s \n", tree_has_key(tree, "F"), "F");
  printf("tree_has_key: \t %d \t %s \n", tree_has_key(tree, "X"), "X");

  item_t *item = tree_get(tree, "D");
  printf("%s \n", item_description(item));
  printf("%d \n", item_price(item));
  
  return 0;
}
