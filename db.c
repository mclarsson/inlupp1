
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

/// Creates new shelf
///
/// \param name Name of shelf (shelf format expected)
/// \param amount Amount of items on shelf
/// \returns pointer to shelf
shelf_t *make_shelf(char *name, int amount)
{
  shelf_t *new = calloc(1, sizeof(shelf_t));
  new->name = name;
  new->amount = amount;
  return new;
}

/// Creates item
///
/// \param description Description of item.
/// \param price Price of item.
/// \returns pointer to item.
item_t *make_item(char *description, int price)
{
  item_t *new = calloc(1, sizeof(item_t));
  new->description = strdup(description);
  new->price = price;
  new->shelves = list_new();
  return new;
}

/// Adds shelf to item
///
/// \param item Item to add to
/// \param name Name of shelf
/// \param amount Amount of item on shelf
void add_shelf(item_t *item, char *name, int amount)
{
  shelf_t *new = make_shelf(name, amount);
  list_append(item->shelves, new);
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
      item_t *item = input_item();
      tree_insert(tree, name, item);
    }
}


//
// Functions
//

bool is_valid_menu_int(K *products, int cur_page, int page_size, int opt1, int opt2, int input)
{
  int page_mod_input = (cur_page*page_size)+input;
  if(products[page_mod_input] == NULL || input < 0)
    {
      if(input == opt1 || input == opt2)
	{
	  return true;
	}
      else
	{
	  return false;
	}
    }
  return true;
}

char *select_goods(tree_t *tree)
{
  //int size = tree_size(tree);
  int page_size = 20;
  //int pages_to_view = 1;
  K *products = tree_keys(tree);
  int input = -1;
  int current_page = 0;
  int opt1 = 21;
  int opt2 = 22;

  while(true)
    {
      for(int i = 0+(current_page*page_size); i < page_size+(current_page*page_size); i++)
	{
	  if(products[i] != NULL)
	    {
	      printf("%d %s\n", (i%page_size)+1, products[i]);
	    }
	}

      while(is_valid_menu_int(products, current_page, page_size, opt1, opt2, input) == false)
	{
	  input = ask_question_int("\nChoose a product (number)\n[21] Next page\n[22] Previous page");
	}
      
      if(input == opt1)
	{
	  current_page += 1;
	}
      else if(input == opt2)
	{
	  if(current_page > 0)
	    {
	      current_page -= 1;
	    }
	}
      else
	{
	  char *name = strdup(products[input+(page_size*current_page)-1]);
	  return name;
	}
    }
}

/// Outputs entire catalog in list format.
///
/// \param tree Tree containing catalog.
void list_goods(tree_t *tree)
{
  int size = tree_size(tree);
  K *items = tree_keys(tree);
  int page_size = 20;
  // Current index for iteration through items
  int index = 0;
  int current_page = 1;
  bool view_next = true;
  
  while (size > index && view_next)
    {
      printf("Sida: %d \n\n", current_page);
      
      // List items
      int max;
      if (current_page * page_size > size)
	{
	  max = size - index;
	}
      else
	{
	  max = page_size;
	}
      
      for (int k = 1; k <= max; ++k, ++index)
	{
	  printf("%d.\t%s\n", k, items[index]);
	}

      // Only ask for next page if not all items have been listed
      if (size == index || ask_question_char("\nSe nästa sida? (y / n)") != 'y')
	{
	  view_next = false;
	}

      ++current_page;
    } 
}

void display_goods(tree_t *tree)
{
  char *goods = select_goods(tree);
  item_t *item = tree_get(tree, goods);
  list_t *shelves = item->shelves;
  for(int i = 0; i < list_length(shelves); i++)
    {
      shelf_t *tmp_shelf = list_get(shelves, i);
      printf("Name: %s \nDescription: %s \nPrice : %d \nShelf: %s \nAmount: %d", goods, item->description, item->price, tmp_shelf->name, tmp_shelf->amount);
    }
}

bool shelf_exists(tree_t *tree, char *shelf)
{
  L *products = tree_elements(tree);
  int i = 0;

  while(true)
    {
      if(products[i] != NULL)
	{
	  item_t *tmp_item = products[i];
	  list_t *shelves = tmp_item->shelves;
	  for(int x = 0; x < list_length(shelves); x++)
	    {
	      shelf_t *tmp_shelf = list_get(shelves, x);
	      if(strcmp(tmp_shelf->name, shelf) == 0)
		{
		  return true;
		}
	    }
	  i++;
	}
      else
	{
	  return false;
	}
    }
  
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
      printf("Nuvarande beskrivning: %s\n", tmp_item->description);
      strcpy(tmp_item->description, ask_question_string("Vad vill du ändra beskrivningen till?"));
      break;

    case 'P':
      printf("Nuvarande pris: %d\n", tmp_item->price);
      tmp_item->price = ask_question_int("Vad vill du ändra priset till?");
      break;

    case 'L':
      {
	for(int i = 0; i < list_length(shelves); i++)
	  {
	    shelf_t *base_shelf_shelfname = list_get(shelves, i);
	    printf("Nuvarande lagerhylla: %s \n", base_shelf_shelfname->name);
	    char *tmp_shelf = "Z9999";
	    tmp_shelf = ask_question_shelf("Vad vill du ängra lagerhyllan till? Du får inte välja en som redan finns.");
	
	    while(shelf_exists(tree, tmp_shelf))
	      {
		tmp_shelf = ask_question_shelf("Vad vill du ängra lagerhyllan till? Du får inte välja en som redan finns.");
	      }
	    strcpy(base_shelf_shelfname->name, tmp_shelf);
	  }
	break;
      }

    case 'T':
      {
	for(int i = 0; i < list_length(shelves); i++)
	  {
	    shelf_t *base_shelf_amount = list_get(shelves, i);
	    printf("Nuvarande lagerhylla: %s\nNuvarande antal: %d\n", base_shelf_amount->name, base_shelf_amount->amount);
	    int tmp_amount = ask_question_int("Vad vill du ändra antalet till?");
	    base_shelf_amount->amount = tmp_amount;
	  }
	break;
      }

    default:
      puts("error");
      break;
    }
}
