#ifndef Ciga_H_INCLUDED
#define Ciga_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Ciga object]
*/
typedef struct _Ciga
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Ciga;
Elements *New_Ciga(int label);
void Ciga_update(Elements *self);
void Ciga_interact(Elements *self, Elements *tar);
void Ciga_draw(Elements *self);
void Ciga_destory(Elements *self);

#endif
