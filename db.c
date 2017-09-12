
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

//
// Types
//

typedef struct item
{
  char *name;
  char *description;
  int price;
  char *shelf;
  int amount;
} item_t;

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

char *magick(char *a1[], char *a2[], char *a3[], int length)
{
  char buf[255];
  int c = 0;
  
  int r = random() % length;
  char *s = a1[r];
  for (int i = 0; i < strlen(s); i++, c++) {
    buf[c] = s[i];
  }

  buf[c++] = '-';
  
  r = random() % length;
  s = a2[r];
  for (int i = 0; i < strlen(s); i++, c++) {
    buf[c] = s[i];
  }
  
  buf[c++] = ' ';
  
  r = random() % length;
  s = a3[r];
  for (int i = 0; i < strlen(s); i++, c++) {
    buf[c] = s[i];
  }
  
  buf[c] = '\0';
  
  return strdup(buf);
}

void list_db(item_t *items, int no_items)
{
  for (int i = 0; i < no_items; i++) {
    printf("%d.\t%s \n", i + 1, items[i].name);
  }
}

int request_index(int db_siz)
{
  int i = -1;
  do {
    printf("Enter an index between %d and %d\n", 1, db_siz);
    i = ask_question_int("Index:");
  } while(!(i > 0 && i <= db_siz));

  // user enters listed index
  i--;
  
  return i;
}

void edit_db(item_t *db, int db_siz)
{
  int i = request_index(db_siz);
  
  print_item(&db[i]);
  item_t it = input_item();
  db[i] = it;
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

char ask_question_menu()
{
  print_menu();

  char menu_items[] = "LlTtRrGgHhAa";
  char c;
  
  do {
    // Ask for c while c is not in menu_items
    c = fgetc(stdin);
  } while (strchr(menu_items, c) == NULL);

  clear_input_buffer();
  return toupper(c);
}

int add_item_to_db(item_t *db, int db_siz)
{
  db[db_siz] = input_item();
  return db_siz + 1;
}

int remove_item_from_db(item_t *db, int db_siz)
{
  list_db(db, db_siz);
  int index = request_index(db_siz);

  item_t cur, prev = db[db_siz - 1];
  for (int i = db_siz - 2; i >= index; i--) {
    cur = db[i];
    db[i] = prev;
    prev = cur;
  }

  return db_siz - 1;
}

int event_loop(item_t *db, int db_siz)
{
  char input;
  int org_size = db_siz;
  do {

    input = ask_question_menu();

    // TODO
    if (db_siz > org_size) {
      db_siz = org_size;
    }
    
    switch (input)
      {
      case 'L':
	db_siz = add_item_to_db(db, db_siz);
	break;
	
      case 'T':
	db_siz = remove_item_from_db(db, db_siz);
	break;

      case 'R':
	edit_db(db, db_siz);
	break;
	
      case 'G':
	fputs("Not yet implemented! \n", stdout);
	break;
	
      case 'H':
	list_db(db, db_siz);
	break;
      default:
	puts("INPUT ERROR");
	break;
      }
    
  } while (input != 'A');

  return 0;
}

//
// Main
//

int main(int argc, char *argv[])
{
  
  srand( time(NULL) );
  
  char *array1[] = { "Laser",        "Polka",    "Extra" };
  char *array2[] = { "förnicklad",   "smakande", "ordinär" };
  char *array3[] = { "skruvdragare", "kola",     "uppgift" };
  
  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0;    // Antalet varor i arrayen just nu

    int items = atoi(argv[1]); // Antalet varor som skall skapas

    if (items > 0 && items <= 16)
    {
      for (int i = 0; i < items; ++i)
      {
        // Läs in en vara, lägg till den i arrayen, öka storleksräknaren
        item_t item = input_item();
        db[db_siz] = item;
        ++db_siz;
      }
    }
    else
    {
      puts("Sorry, must have [1-16] items in database.");
      return 1; // Avslutar programmet!
    }

    for (int i = db_siz; i < 16; ++i)
      {
        char *name = magick(array1, array2, array3, 3); /// Lägg till storlek
        char *desc = magick(array1, array2, array3, 3); /// Lägg till storlek
        int price = random() % 200000;
	int amount = random() % 100;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, amount, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     // Skriv ut innehållet
    return event_loop(db, db_siz);
  }
  
  return 0;
}
