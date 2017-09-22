
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

void event_loop()
{
  //tree_t *catalog = tree_new();
  
  puts("\n Välkommen till lagerhantering 1.0");
  puts(" ================================= \n");

  char input;
  
  while (true)
    {
      print_menu();
      input = ask_question_char(" > ");

      switch (input) {
      case 'L':
	break;
      }      
    }
}

int main (void)
{
  // Start program
  event_loop();
  
  return 0;
}
