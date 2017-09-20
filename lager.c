
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "tree.h"

char ask_question_menu()
{
  // print_menu();

  //char menu_items[] = "LlTtRrGgHhAa";
  char c = 'c';

  /*
  do {
    // Ask for c while c is not in menu_items
    c = ask_question_char("Vad vill du göra?");
  } while (strchr(menu_items, c) == NULL);
  */
  return toupper(c);
}

void print_edit_menu()
{
  fputs("[B]eskrivning\n", stdout);
  fputs("[P]ris\n", stdout);
  fputs("[L]agerhylla\n", stdout);
  fputs("An[t]aö\n", stdout);
}

char ask_question_edit_menu()
{
  //print_menu();

  //char menu_items[] = "BbPpLlTt";
  char c = 'c';
  /*
  do {
    // Ask for c while c is not in menu_items
    c = ask_question_char("Välj rad eler [a]vbryt");
  } while (strchr(menu_items, c) == NULL);
  */
  return toupper(c);
}


void print_menu()
{
  fputs("[L]ägga till en vara\n", stdout);
  fputs("[T]a bort en vara \n", stdout);
  fputs("[R]edigera en vara\n", stdout);
  fputs("Ån[g]ra senaste ändringen\n", stdout);
  fputs("Lista [h]ela varukatalogen\n", stdout);
  fputs("[A]vsluta\n", stdout);
}

void exit_program()
{
  return;
}

int main (void)
{
  tree_t *tree = tree_new();
  free(tree);
  
  return 0;
}
