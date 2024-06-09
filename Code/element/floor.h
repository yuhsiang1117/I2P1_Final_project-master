#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int map_data[6][6];
} Floor;

Elements *New_Floor(int label);
void _Floor_load_map(Floor *floor);
void Floor_update(Elements *self);
void Floor_interact(Elements *self, Elements *tar);
void Floor_draw(Elements *self);
void Floor_destory(Elements *self);

#endif
