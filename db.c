
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "tree.h"

//
// Types
//

typedef struct shelf shelf_t;

struct item {
  char *description;
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

/**
 * print_item
 */
void print_item(item_t *i)
{
  int a = i->price / 100;
  int b = i->price % 100;
  printf("Name:  \t %s \n", i->name);
  printf("Desc:  \t %s \n", i->description);
  printf("Price: \t %d.%d \n", a, b);
  printf("Shelf: \t %s \n", i->shelf);
  printf("Amount:\t %d \n", i->amount);
}

/**
 * make_item
 */
item_t make_item(char *name, char *description, int price, int amount, char *shelf)
{
  return (item_t) { .name = strdup(name), .description = strdup(description), .price = price, .shelf = strdup(shelf), .amount = amount };
}

/**
 * input_item
 */
item_t input_item()
{
  
  char name[255];
  char description[255];
  int price;
  char shelf[255];
  int amount;
  
  strcpy(name, ask_question_string("Enter name:") );
  strcpy(description, ask_question_string("Enter description:") );
  price = ask_question_int("Enter price:");
  strcpy(shelf, ask_question_shelf("Enter shelf:") );
  amount = ask_question_int("Enter amount:");
  
  return make_item(name, description, price, amount, shelf);
}

bool shelf_in_use(item_t *new, item_t *db, int db_siz)
{
  for(int i=0;i<db_siz;i++)
    {
      if(db[db_siz].shelf == new->shelf && db[db_siz].name != new->name)
	{
	  return true;
	}
    }
  return false;
}

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

/*
item_t input_existing_item(char *name, char *description, int price)
{
  
  char item_name[255];
  char item_description[255];
  int item_price;
  char shelf[255];
  int amount;
  
  strcpy(item_name, name);
  strcpy(item_description, description);
  item_price = price;
  strcpy(shelf, ask_question_shelf("Enter shelf:") );
  amount = ask_question_int("Enter amount:");
  
  return make_item(item_name, item_description, item_price, amount, shelf);
}

void remove_goods(tree_t *tree)
{
  return;
}

void edit_goods(tree_t *tree)
{
  char name = "test";
  
  list_t list = tree_get(tree, name);
  
  for(int i = 0; i < list_length(list); i++)
    {
      
      char input = ask_question_edit_menu();
      item_t tmp_item = list_get(list, i);
      
      switch(input)
	{	  
	case 'B':
	  printf("Nuvarande beskrivning: %s", tmp_item->description);
	  char tmp_info = ask_question_string("Vad vill du ändra beskrivningen till?");
	  tmp_item->description = tmp_info;
	  break;

	case 'P':
	  printf("Nuvarande pris: %d", tmp_item->price);
	  int tmp_info = ask_question_int("Vad vill du ändra priset till?");
	  tmp_item->price = tmp_info;
	  break;

	case 'L':
	  printf("Nuvarande lagerhylla: %s", tmp_item->shelf);
	  char tmp_info = ask_question_shelf("Vad vill du ängra lagerhyllan till?");
	  tmp_item->shelf = tmp_info;
	  break;

	case 'T':
	  printf("Nuvarande antal: %d", tmp_item->price);
	  int tmp_info = ask_question_int("Vad vill du ändra antalet till?");
	  tmp_item->price = tmp_info;
	  break;

	default:
	  puts("error");
	  break;
	}
    }
}


void add_goods(tree_t *tree)
{
  char name[255] = ask_question_string("Enter name:");
  if(tree_has_key(tree, name))
    {
      puts("Varan finns redan, använder samma beskrivning & pris!");
      list_t *list = tree_get(tree, item->name);
      item_t existing_item = list_first(list);
      item_t item = input_existing_item(name, existing_item->description, existing_item->price);
      for(int i=0; i < list_length(list); i++)
	{
	  char *shelf = list_get(list, i)->shelf;
	  if(shelf == item->shelf)
	    {
	      list_get(list, i)->amount += item->amount;
	      return;
	    }
	}
      list_append(list, item);
    }
  else
    {
      item_t item = input_item(name);
      list_t *list = new_list();
      list_append(list, item);
      tree_insert(tree, item->name, list);
    }
  return;
}
*/
