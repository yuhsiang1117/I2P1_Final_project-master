#include "beer.h"
#include "../shapes/Rectangle.h"
/*
   [Beer function]
*/
Elements *New_Beer(int label)
{
    Beer *pDerivedObj = (Beer *)malloc(sizeof(Beer));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/beer.png");
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
    pObj->Update = Beer_update;
    pObj->Interact = Beer_interact;
    pObj->Draw = Beer_draw;
    pObj->Destroy = Beer_destory;
    return pObj;
}
void Beer_update(Elements *self) {}
void Beer_interact(Elements *self, Elements *tar) {}
void Beer_draw(Elements *self)
{
    Beer *Obj = ((Beer *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Beer_destory(Elements *self)
{
    Beer *Obj = ((Beer *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
