#ifndef HANDCUFF_H_INCLUDED
#define HANDCUFF_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Handcuff object]
*/
typedef struct _Handcuff
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Handcuff;
Elements *New_Handcuff(int label);
void Handcuff_update(Elements *self);
void Handcuff_interact(Elements *self, Elements *tar);
void Handcuff_draw(Elements *self);
void Handcuff_destory(Elements *self);

#endif
