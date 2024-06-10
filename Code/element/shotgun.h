#ifndef shotgun_H_INCLUDED
#define shotgun_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [shotgun object]
*/
typedef struct _shotgun
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int state;
} shotgun;

typedef enum shotgun_state
{
    unused,
    used
} shotgun_state;

Elements *New_shotgun(int label);
void shotgun_update(Elements *self);
void shotgun_interact(Elements *self, Elements *tar);
void shotgun_draw(Elements *self);
void shotgun_destory(Elements *self);

#endif
