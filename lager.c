
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "tree.h"
#include "list.h"
#include "db.h"

void exit_program()
{
  exit(0);
}


// Helper function for adding stuff to catalog
void populate_catalog(tree_t *catalog, int size)
{ 
  for (int i = 0; i < size; i++)
    {
      // Generate random key
      int name_length = 10;
      char name[name_length];
      for (int i = 0; i < name_length; ++i)
	{
	  name[i] = 'A' + rand() % 15;
	}
      name[name_length] = '\0';
      
      item_t *item = make_item("desc", 12);
      char *shelfname = calloc(4, sizeof(char));
      sprintf(shelfname, "%s%d", "A", i);
      add_shelf(item, shelfname, i);
      tree_insert(catalog, name, item);
    }
}

int event_loop()
{
  tree_t *catalog = tree_new();

  populate_catalog(catalog, 1);
  
  puts("\n\n\tVälkommen till lagerhantering 1.0");
  puts("\t================================= \n");
  
  char input;
  
  while (true)
    {
      print_menu();
      input = toupper(ask_question_char(" > "));

      switch (input)
	{
	case 'L':
	  // Add item
	  add_goods(catalog);
	  break;

	case 'H':
	  // List catalog
	  list_goods(catalog);
	  break;

	case 'T':
	  //remove goods
	  remove_goods(catalog);
	  break;

	case 'R':
	  //edit goods
	  edit_goods(catalog);
	  break;

	case 'G':
	  //undo
	  //undo_action();
	  break;
	         	  
	case 'A':
	  // Exit
	  exit_program();
	  //return 0;
	  break;

	default:
	  fprintf(stdout, "%c är inte ett kommando \n", input);
	    break;
	}      
    }
}

int main (void)
{
  // Start program
  return event_loop();
}
