#include "player1.h"
#include "../shapes/Rectangle.h"
/*
   [player1 function]
*/
Elements *New_player1(int label)
{
    player1 *pDerivedObj = (player1 *)malloc(sizeof(player1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/player1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->hp = 10;
    pDerivedObj->x = 65;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    for(int i=0;i<6;i++){
        pDerivedObj->item[i] = 0;
    }
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = player1_update;
    pObj->Interact = player1_interact;
    pObj->Draw = player1_draw;
    pObj->Destroy = player1_destory;
    return pObj;
}
void player1_update(Elements *self) {}
void player1_interact(Elements *self, Elements *tar) {}
void player1_draw(Elements *self)
{
    player1 *Obj = ((player1 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void player1_destory(Elements *self)
{
    player1 *Obj = ((player1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
