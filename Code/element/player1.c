#include "player1.h"
#include "../shapes/Rectangle.h"
/*
   [player1 function]
*/
Elements *New_player1(int label)
{
    player1 *pDerivedObj = (player1 *)malloc(sizeof(player1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/player1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 85;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hp = 4;
    for(int i=0;i<6;i++){
        pDerivedObj->item[i] = 0;
    }
    pDerivedObj->state = nothing;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = player1_update;
    pObj->Interact = player1_interact;
    pObj->Draw = player1_draw;
    pObj->Destroy = player1_destory;
    printf("player1_init_finish\n");
    return pObj;
}
void player1_update(Elements *self) {
    player1 *p1 = ((player1 *)(self->pDerivedObj));
    // printf("%d\n", state);
    int push1, push1_next;
    if(key_state[ALLEGRO_KEY_1]){
        if(state == P1_turn_L){
            //shoot my self
            //printf("key1_down\n");
            if(bullet_arr[bullet_num-1]==1){
                p1->state = Shoot_P1;
            }else{
                p1->state = Blank_p1;
            }
        }else if(key_state[ALLEGRO_KEY_2]){
            //shoot him
            if(bullet_arr[bullet_num-1]==1){
                p1->state = Shoot_P2;
            }else{
                p1->state = Blank_p2;
            }
        }else{
            p1->state = nothing;
            
        }
    }else{
        p1->state = p1->state;
    }
    
}
void player1_interact(Elements *self, Elements *tar) {

}
void player1_draw(Elements *self)
{
    player1 *Obj = ((player1 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void player1_destory(Elements *self)
{
    player1 *Obj = ((player1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
