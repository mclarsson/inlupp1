
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "db.h"
#include "utils.h"
#include "list.h"

//
// Types
//

struct item {
  char *description[255];
  int price;
  list_t *shelves;
};

struct shelf {
  char *name;
  int amount;
};

//
// Functions
//
/*
void list_goods(tree_t *tree)
{
  int size = tree_size(tree);
  int page_size = 20;
  int pages_to_view = 1;
  T *products = tree_elements(tree);

  if (size > page_size)
    {
      do
	{
	  pages_to_view = ask_question_int("Hur många sidor vill du se?");
	} while (pages_to_view > size / page_size);
    }

  int index = 0;
  for (int p = 0; p < pages_to_view; ++p)
    {
      int max = size - page_size * p < page_size ? size - page_size * p : page_size;
      for (int i = 1; i <= max; ++i, ++index)
	{
	  printf("%d: %s", i, products[index]->name);
	}
    }
}
*/
