
#include <stdbool.h>
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


// Helper function for adding stuff to catalog
void populate_catalog(tree_t *catalog)
{ 
  for (int i = 0; i < 50; i++)
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
      tree_insert(catalog, name, item);
    }
}

int event_loop()
{
  tree_t *catalog = tree_new();

  populate_catalog(catalog);
  
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

	case 'A':
	  // Exit
	  return 0;
	  break;
	}      
    }
}

int main (void)
{
  // Start program
  return event_loop();
}
