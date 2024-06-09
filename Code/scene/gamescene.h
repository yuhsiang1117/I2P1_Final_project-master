#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/beer.h"
#include "../element/table.h"
#include "../element/ciga.h"
#include "../element/key.h"
#include "../element/magnifier.h"
#include "../element/handcuff.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [game scene object]
*/
typedef enum EleType
{   
    Beer_L,
    Table_L,
    Ciga_L,
    Key_L,
    Magnifier_L,
    Handcuff_L,
    Player1_L,
    Player2_L
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;

} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
