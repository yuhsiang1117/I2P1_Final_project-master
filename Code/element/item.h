#ifndef ITEM_H
#define ITEM_H

typedef struct {
    const char* name;
    int value;
} Item;

void initialize_items();
Item draw_random_item();

#endif // ITEMS_H