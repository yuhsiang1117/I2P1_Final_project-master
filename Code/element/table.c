#include "Table.h"
#include "../shapes/Rectangle.h"
/*
   [Table function]
*/
Elements *New_Table(int label)
{
    Table *pDerivedObj = (Table *)malloc(sizeof(Table));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/table.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH/2 - pDerivedObj->width / 2;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Table_update;
    pObj->Interact = Table_interact;
    pObj->Draw = Table_draw;
    pObj->Destroy = Table_destory;
    return pObj;
}
void Table_update(Elements *self) {}
void Table_interact(Elements *self, Elements *tar) {}
void Table_draw(Elements *self)
{
    Table *Obj = ((Table *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Table_destory(Elements *self)
{
    Table *Obj = ((Table *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
