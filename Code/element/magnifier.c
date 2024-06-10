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
void Magnifier_update(Elements *self) {
    Magnifier *magnifier = (Magnifier*)(self->pDerivedObj);
    ElementVec allEle = _Get_all_elements(scene);
    Elements* ele1 =  allEle.arr[Player1_L];
    Elements* ele2 =  allEle.arr[Player2_L];
    player1* p1=(player1*)(ele1->pDerivedObj);
    player2* p2=(player2*)(ele2->pDerivedObj);
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    if(state == P1_turn_L){
        if(p1->item[Magnifier_num]>0 && mouse_x >= magnifier->x && mouse_x <= magnifier->x+magnifier->width && mouse_y >= magnifier->y && mouse_y <= magnifier->y+magnifier->height && ev.mouse.button == 1){
            magnifier->state = 1;
            printf("use magnifier");
            p1->item[Magnifier_num]--;
        }
    }
    if(state == P2_turn_L){
        if(p2->item[Magnifier_num]>0 && mouse_x >= (WIDTH-magnifier->width) && mouse_x <= WIDTH && mouse_y >= magnifier->y && mouse_y <= magnifier->y+magnifier->height && ev.mouse.button == 1)
            magnifier->state = 1;
    }
}
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
