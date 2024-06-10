#ifndef BEER_H_INCLUDED
#define BEER_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "../global.h"
/*
   [Beer object]
*/
typedef struct _Beer
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int state;
} Beer;
Elements *New_Beer(int label);
void Beer_update(Elements *self);
void Beer_interact(Elements *self, Elements *tar);
void Beer_draw(Elements *self);
void Beer_destory(Elements *self);

#endif
