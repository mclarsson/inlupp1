
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
  char *description;
  int price;
  list_t *shelves;
};

struct shelf {
  char *name;
  int amount;
};

shelf_t *make_shelf(char *name, int amount)
{
  shelf_t *new = calloc(1, sizeof(shelf_t));
  new->name = name;
  new->amount = amount;
  return new;
}

item_t *make_item(char *description, int price)
{
  item_t *new = calloc(1, sizeof(item_t));
  new->description = description;
  new->price = price;
  new->shelves = list_new();
  return new;
}

void add_shelf(item_t *item, char *name, int amount)
{
  shelf_t *new = make_shelf(name, amount);
  list_append(item->shelves, new);
}

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
