
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "db.h"
#include "utils.h"
#include "list.h"
#include "tree.h"

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

shelf_t make_shelf(char *shelf, int amount)
{
  return (shelf_t) { .name = strdup(shelf), .amount = amount};
}

item_t make_item(char *description, int price, int amount, char *shelf)
{
  list_t *shelves = list_new();
  shelf_t new_shelf = make_shelf(shelf, amount);
  list_append(shelves, &new_shelf);
  return (item_t) { .description = strdup(description), .price = price, .shelves = shelves};
}


item_t input_item()
{

  char description[255];
  int price;
  char shelf[255];
  int amount;

  strcpy(description, ask_question_string("Enter description:") );
  price = ask_question_int("Enter price:");
  strcpy(shelf, ask_question_shelf("Enter shelf:") );
  amount = ask_question_int("Enter amount:");
  
  return make_item(description, price, amount, shelf);
}


void input_existing_item(list_t *shelves)
{
  
  char shelf[255];
  int amount;
  
  strcpy(shelf, ask_question_shelf("Enter shelf:") );
  amount = ask_question_int("Enter amount:");

  for(int i = 0; i < list_length(shelves); i++)
    {
      shelf_t *tmp_shelf = list_get(shelves, i);
      if(tmp_shelf->name == shelf)
	{
	  tmp_shelf->amount += amount;
	  return;
	}
    }

  shelf_t new_shelf = make_shelf(shelf, amount);
  list_append(shelves, &new_shelf);
  
  return;
}


void remove_goods(tree_t *tree)
{
  return;
}

/*
void edit_goods(tree_t *tree)
{
  char *name = "test";
  
  item_t tmp_item = tree_get(tree, name);
  list_t *shelves = tmp_item.shelves;
  
  char input = ask_question_edit_menu();
      
  switch(input)
    {	  
    case 'B':
      printf("Nuvarande beskrivning: %s", tmp_item.description);
      char *tmp_desc = ask_question_string("Vad vill du ändra beskrivningen till?");
      tmp_item.description = strdup(tmp_desc);
      break;

    case 'P':
      printf("Nuvarande pris: %d", tmp_item.price);
      int tmp_price = ask_question_int("Vad vill du ändra priset till?");
      tmp_item.price = tmp_price;
      break;

    case 'L':
      printf("Nuvarande lagerhylla: %s", list_get(shelves, 0).name);
      char *tmp_shelf = ask_question_shelf("Vad vill du ängra lagerhyllan till?");
      for(int i = 0; i < list_length(shelves); i++)
	{
	  list_get(shelves, i).name = strdup(tmp_shelf);
	}
      break;

    case 'T':
      printf("Nuvarande antal: %d", list_get(shelves, 0).price);
      int tmp_amount = ask_question_int("Vad vill du ändra antalet till?");
            for(int i = 0; i < list_length(shelves); i++)
	{
	  list_get(shelves, i).amount = tmp_amount;
	}
      break;

    default:
      puts("error");
      break;
    }
}
*/

void add_goods(tree_t *tree)
{
  char name[255];
  strcpy(name, ask_question_string("Enter name:"));
  if(tree_has_key(tree, name))
    {
      puts("Varan finns redan, använder samma beskrivning & pris!");
      item_t *item = tree_get(tree, name);
      list_t *shelves = item->shelves;
      input_existing_item(shelves);
    }
  else
    {
      item_t item = input_item(name);
      tree_insert(tree, name, &item);
    }
  return;
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
  char *products = tree_keys(tree);

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
	  printf("%d: %s", i, products[index]);
	}
    }
}
*/
