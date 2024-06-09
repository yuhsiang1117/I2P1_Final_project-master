#include "handcuff.h"
#include "../shapes/Rectangle.h"
/*
   [Handcuff function]
*/
Elements *New_Handcuff(int label)
{
    Handcuff *pDerivedObj = (Handcuff *)malloc(sizeof(Handcuff));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/handcuff.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 65;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Handcuff_update;
    pObj->Interact = Handcuff_interact;
    pObj->Draw = Handcuff_draw;
    pObj->Destroy = Handcuff_destory;
    return pObj;
}
void Handcuff_update(Elements *self) {}
void Handcuff_interact(Elements *self, Elements *tar) {}
void Handcuff_draw(Elements *self)
{
    Handcuff *Obj = ((Handcuff *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Handcuff_destory(Elements *self)
{
    Handcuff *Obj = ((Handcuff *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
