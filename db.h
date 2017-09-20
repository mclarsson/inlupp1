#ifndef __db_h__
#define __db_h__

typedef struct shelf shelf_t;

typedef struct item item_t;

shelf_t *make_shelf(char *name, int amount);

item_t *make_item(char *description, int price);

#endif
