#include "magnifier.h"
#include "../shapes/Rectangle.h"
/*
   [Magnifier function]
*/
Elements *New_Magnifier(int label)
{
    Magnifier *pDerivedObj = (Magnifier *)malloc(sizeof(Magnifier));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Magnifier.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 85;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Magnifier_update;
    pObj->Interact = Magnifier_interact;
    pObj->Draw = Magnifier_draw;
    pObj->Destroy = Magnifier_destory;
    return pObj;
}
void Magnifier_update(Elements *self) {}
void Magnifier_interact(Elements *self, Elements *tar) {}
void Magnifier_draw(Elements *self)
{
    Magnifier *Obj = ((Magnifier *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Magnifier_destory(Elements *self)
{
    Magnifier *Obj = ((Magnifier *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
