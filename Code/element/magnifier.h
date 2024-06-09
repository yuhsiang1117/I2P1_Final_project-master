#ifndef Magnifier_H_INCLUDED
#define Magnifier_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Magnifier object]
*/
typedef struct _Magnifier
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Magnifier;
Elements *New_Magnifier(int label);
void Magnifier_update(Elements *self);
void Magnifier_interact(Elements *self, Elements *tar);
void Magnifier_draw(Elements *self);
void Magnifier_destory(Elements *self);

#endif
