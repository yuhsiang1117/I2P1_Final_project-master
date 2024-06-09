#ifndef CHEST_H_INCLUDED
#define CHEST_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>
#include "../global.h"
#include "player1.h"

/*
   [Chest object]
*/
typedef enum ChestType
{
    appear = 0,
    opened,
} ChestType;
typedef struct _Chest
{
    int x, y;
    int width, height;              // the width and height of image
    int state;                      // the state of Chest
    ALGIF_ANIMATION *gif_status[2]; // gif for each state. 0: appear, 1: open
    ALLEGRO_SAMPLE_INSTANCE *open_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    Shape *hitbox; // the hitbox of object
} Chest;
Elements *New_Chest(int label);
void _Chest_update_position(Elements *self, int dx, int dy);
void Chest_update(Elements *self);
void Chest_interact(Elements *self, Elements *target);
void Chest_draw(Elements *self);
void Chest_destory(Elements *self);
int Chest_drawitem();

#endif
