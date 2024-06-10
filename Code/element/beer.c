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
    pDerivedObj->x = 0;
    pDerivedObj->y = pDerivedObj->height;
    pDerivedObj->state = 0;
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
void Beer_update(Elements *self){
    Beer *beer = (Beer*)(self->pDerivedObj);
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
        if(p1->item[Beer_num]>0 && mouse_x >= beer->x && mouse_x <= beer->x+beer->width && mouse_y >= beer->y && mouse_y <= beer->y+beer->height && ev.mouse.button == 1){
            beer->state = 1;
            printf("use beer");
            p1->item[Beer_num]--;
        }
            
    }
    if(state == P2_turn_L){
        if(p2->item[Beer_num]>0 && mouse_x >= (WIDTH-beer->width) && mouse_x <= WIDTH && mouse_y >= beer->y && mouse_y <= beer->y+beer->height && ev.mouse.button == 1)
            beer->state = 1;
    }
}
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
