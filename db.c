
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

char *item_description(item_t *item)
{
  return item->description;
}

int item_price(item_t *item)
{
  return item->price;
}

list_t *item_shelves(item_t *item)
{
  return item->shelves;
}

item_t *input_item()
{
  char description[255];
  int price;

  strcpy(description, ask_question_string("Enter description:") );
  price = ask_question_int("Enter price:");
  
  return make_item(description, price);
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

  shelf_t *new_shelf = make_shelf(shelf, amount);
  list_append(shelves, &new_shelf);
  
  return;
}


void remove_goods(tree_t *tree)
{
  return;
}

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
      item_t *item = input_item(name);
      tree_insert(tree, name, item);
    }
  return;
}


//
// Functions
//

bool is_valid_int(int input, int min, int max, int opt1, int opt2)
{
  if((input >= min && input <= max) || input == opt1 || input == opt2)
    {
      return true;
    }
  return false;
}

char *select_goods(tree_t *tree)
{
  //int size = tree_size(tree);
  int page_size = 20;
  //int pages_to_view = 1;
  K *products = tree_keys(tree);
  int input = 0;
  int current_page = 0;
  int opt1 = 21;
  int opt2 = 22;
  int no_products = sizeof(products)/sizeof(k);
    
  while(true)
    {
      for(int i = 0+(current_page*page_size); i < page_size+(current_page*page_size); i++)
	{
	  if(i < no_products)
	    {
	      printf("%d %s", i%page_size, products[i]);
	    }
	}
      while(is_valid_int(input, , ,opt1, opt2) == false)
	{
	  input = ask_question_int("Choose a product (number),\n[21] Next page\n[22] Previous page]");
	}
      
      if(input == 21)
	{
	  current_page += 1;
	}
      else if(input == 22 && current_page > 0)
	{
	  current_page += -1;
	}
      else if(input+(current_page*page_size) > no_products)
	{
	  puts("Ogiltigt val");
	}
      else
	{
	  char *name = strdup(products[input+(page_size*current_page)]);
	  return name;
	}
    }
}

void list_goods(tree_t *tree)
{
  char *goods = select_goods(tree);
  item_t *item = tree_get(tree, goods);
  list_t *shelves = item->shelves;
  for(int i = 0; i < list_length(shelves); i++)
    {
      shelf_t *tmp_shelf = list_get(shelves, i);
      printf("Name: %s \nDescription: %s \nPrice : %d \nShelf: %s \nAmount: %d", goods, item->description, item->price, tmp_shelf->name, tmp_shelf->amount);
    }
  
  /*
    KOMMENTAR: man ska kunna bläddra mellan sidor med max 20, inte se allt samtidigt
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
  */
}

bool shelf_exists(tree_t *tree, char *shelf)
{
  /*
  item_t **products = tree_elements(tree);
  for(int i = 0; i < (sizeof(products)/sizeof(item_t)); i++)
    {
      list_t *shelves = products[i]->shelves;
      for(int x = 0; i < list_length(shelves); x++)
	{
	  shelf_t *tmp_shelf = list_get(shelves, x);
	  if(tmp_shelf->name == shelf)
	    {
	      return true;
	    }
	}
    }
  */
  return false;
}

void edit_goods(tree_t *tree)
{
  char *name = select_goods(tree);
  
  item_t *tmp_item = tree_get(tree, name);
  list_t *shelves = tmp_item->shelves;
  
  char input = ask_question_edit_menu();
      
  switch(input)
    {	  
    case 'B':
      printf("Nuvarande beskrivning: %s", tmp_item->description);
      strcpy(tmp_item->description, ask_question_string("Vad vill du ändra beskrivningen till?"));
      break;

    case 'P':
      printf("Nuvarande pris: %d", tmp_item->price);
      tmp_item->price = ask_question_int("Vad vill du ändra priset till?");
      break;

    case 'L':
      {
	shelf_t *base_shelf_shelfname = list_first(shelves);
	printf("Nuvarande lagerhylla: %s", base_shelf_shelfname->name);
	char *tmp_shelf = base_shelf_shelfname->name;
	
	while(shelf_exists(tree, tmp_shelf))
	  {
	    tmp_shelf = ask_question_shelf("Vad vill du ängra lagerhyllan till? Du får inte välja en som redan finns.");
	  }
	
	for(int i = 0; i < list_length(shelves); i++)
	  {
	    shelf_t *shelf = list_get(shelves, i);
	    strcpy(shelf->name, tmp_shelf);
	  }
	break;
      }

    case 'T':
      {
	shelf_t *base_shelf_amount = list_first(shelves);
	printf("Nuvarande antal: %d", base_shelf_amount->amount);
	int tmp_amount = ask_question_int("Vad vill du ändra antalet till?");
	for(int i = 0; i < list_length(shelves); i++)
	  {
	    shelf_t *shelf = list_get(shelves, i);
	    shelf->amount = tmp_amount;
	  }
	break;
      }

    default:
      puts("error");
      break;
    }
}
