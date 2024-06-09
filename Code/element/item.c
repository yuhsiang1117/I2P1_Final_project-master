#include "item.h"
#include <stdlib.h>
#include <time.h>

// 定義道具數組
#define NUM_ITEMS 5

static Item items[NUM_ITEMS];

void initialize_items() {
    items[0] = (Item){"beer", 10};
    items[1] = (Item){"ciga", 15};
    items[2] = (Item){"handcuff", 5};
    items[3] = (Item){"key", 20};
    items[4] = (Item){"magnifier", 8};
    // 初始化隨機數生成器
    srand(time(NULL));
}

Item draw_random_item() {
    int index = rand() % NUM_ITEMS;
    return items[index];
}