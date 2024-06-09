#ifndef Table_H_INCLUDED
#define Table_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Table object]
*/
typedef struct _Table
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Table;
Elements *New_Table(int label);
void Table_update(Elements *self);
void Table_interact(Elements *self, Elements *tar);
void Table_draw(Elements *self);
void Table_destory(Elements *self);

#endif
