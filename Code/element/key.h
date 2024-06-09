#ifndef Key_H_INCLUDED
#define Key_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Key object]
*/
typedef struct _Key
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Key;
Elements *New_Key(int label);
void Key_update(Elements *self);
void Key_interact(Elements *self, Elements *tar);
void Key_draw(Elements *self);
void Key_destory(Elements *self);

#endif
