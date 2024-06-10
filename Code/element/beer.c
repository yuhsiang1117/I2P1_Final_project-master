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
    pDerivedObj->y = pDerivedObj->height/2;
    pDerivedObj->state = 0;
    beerstate = 0;
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
        if(p1->item[Beer_num]>0 && mouse_x >= 0 && mouse_x <= 96 && mouse_y >= 120 && mouse_y <= 180 && ev.mouse.button == 1){
            beerstate = 1;
            bulletout = bullet_arr[bullet_num-1];
            bullet_num--;
            printf("use beer");
            p1->item[Beer_num]--;
        }
            
    }
    if(state == P2_turn_L){
        if(p2->item[Beer_num]>0 && mouse_x >= WIDTH-96 && mouse_x <= WIDTH && mouse_y >= 120 && mouse_y <= 180 && ev.mouse.button == 1){
            beerstate = 1;
            bulletout = bullet_arr[bullet_num-1];
            bullet_num--;
            printf("use beer");
            p2->item[Beer_num]--;
        }
    }
}
void Beer_interact(Elements *self, Elements *tar) {}
void Beer_draw(Elements *self)
{
    /*Beer *Obj = ((Beer *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);*/
}
void Beer_destory(Elements *self)
{
    Beer *Obj = ((Beer *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
