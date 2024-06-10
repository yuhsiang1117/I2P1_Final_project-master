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
void Handcuff_update(Elements *self) {
    Handcuff *handcuff = (Handcuff*)(self->pDerivedObj);
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
        if(p1->item[Handcuff_num]>0 && mouse_x >= handcuff->x && mouse_x <= handcuff->x+handcuff->width && mouse_y >= handcuff->y && mouse_y <= handcuff->y+handcuff->height && ev.mouse.button == 1){
            printf("P1 use handcuff");
            handcuff_state = 1;
            p1->item[Handcuff_num]--;
        }
    }
    if(state == P2_turn_L){
        if(p2->item[Handcuff_num]>0 && mouse_x >= (WIDTH-handcuff->width) && mouse_x <= WIDTH && mouse_y >= handcuff->y && mouse_y <= handcuff->y+handcuff->height && ev.mouse.button == 1){
            printf("P2 use handcuff");
            handcuff_state = 1;
            p2->item[Handcuff_num]--;
        }
            
    }
}
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
