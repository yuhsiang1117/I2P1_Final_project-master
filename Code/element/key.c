#include "key.h"
#include "../shapes/Rectangle.h"
/*
   [Key function]
*/
Elements *New_Key(int label)
{
    Key *pDerivedObj = (Key *)malloc(sizeof(Key));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/key.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 105;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Key_update;
    pObj->Interact = Key_interact;
    pObj->Draw = Key_draw;
    pObj->Destroy = Key_destory;
    return pObj;
}
void Key_update(Elements *self) {}
void Key_interact(Elements *self, Elements *tar) {}
void Key_draw(Elements *self)
{
    Key *Obj = ((Key *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Key_destory(Elements *self)
{
    Key *Obj = ((Key *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
