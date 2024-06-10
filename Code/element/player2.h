#ifndef player2_H_INCLUDED
#define player2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "../scene/sceneManager.h"
/*
   [player2 object]
*/
typedef struct _player2
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    int hp;
    int state;
    int item[6];
    int damage
} player2;

typedef enum P2_state
{
    P2_Blank_p1,
    P2_Blank_p2,
    P2_Shoot_P1,
    P2_Shoot_P2,
    P2_nothing
} P2_state;

Elements *New_player2(int label);
void player2_update(Elements *self);
void player2_interact(Elements *self, Elements *tar);
void player2_draw(Elements *self);
void player2_destory(Elements *self);

#endif
