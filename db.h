#ifndef __db_h__
#define __db_h__

#include "list.h"

typedef struct shelf shelf_t;

typedef struct item item_t;

typedef struct tree tree_t;

shelf_t *make_shelf(char *name, int amount);

item_t *make_item(char *description, int price);

void add_shelf(item_t *item, char *name, int amount);

char *item_description(item_t *item);

int item_price(item_t *item);

list_t *item_shelves(item_t *item);

/*
char *select_goods(tree_t *tree)

void list_goods(tree_t *tree)

void edit_goods(tree_t *tree)
*/

#endif
