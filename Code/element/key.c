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
void Key_update(Elements *self) {
    Key *key = (Key*)(self->pDerivedObj);
    ElementVec allEle = _Get_all_elements(scene);
    Elements* ele1 =  allEle.arr[Player1_L];
    Elements* ele2 =  allEle.arr[Player2_L];
    player1* p1=(player1*)(ele1->pDerivedObj);
    player2* p2=(player2*)(ele2->pDerivedObj);
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    /*if(state == P1_turn_L){
        if(p1->item[Key_num]>0 && mouse_x >= key->x && mouse_x <= key->x+key->width && mouse_y >= key->y && mouse_y <= key->y+key->height && ev.mouse.button == 1){
            key->state = 1;
            printf("use key");
            p1->item[Key_num]--;
        }
    }
    if(state == P2_turn_L){
        if(p2->item[Key_num]>0 && mouse_x >= (WIDTH-key->width) && mouse_x <= WIDTH && mouse_y >= key->y && mouse_y <= key->y+key->height && ev.mouse.button == 1)
            key->state = 1;
    }*/
}
void Key_interact(Elements *self, Elements *tar) {}
void Key_draw(Elements *self)
{
    /*Key *Obj = ((Key *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);*/
}
void Key_destory(Elements *self)
{
    Key *Obj = ((Key *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
