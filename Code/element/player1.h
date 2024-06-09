#ifndef player1_H_INCLUDED
#define player1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [player1 object]
*/
typedef enum P1_state
{
    Blank_p1,
    Blank_p2,
    Shoot_P1,
    Shoot_P2,
    nothing
} P1_state;

typedef struct _player1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int hp;
    int state;
    int item[6]; //{0:beer 1:ciga 2:key 3:handcuff 4:mgnifier 5:shotgun}
}player1;

Elements *New_player1(int label);
void player1_update(Elements *self);
void player1_interact(Elements *self, Elements *tar);
void player1_draw(Elements *self);
void player1_destory(Elements *self);

#endif