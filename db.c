
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "tree.h"

//
// Types
//

typedef struct item item_t;

struct item {
  char *name;
  char *description;
  int price;
  char *shelf;
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

void display_goods(tree_t *tree)
{
  return;
}
