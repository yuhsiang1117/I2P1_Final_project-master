#include "player2.h"
#include "../shapes/Rectangle.h"
/*
   [player2 function]
*/
Elements *New_player2(int label)
{
    player2 *pDerivedObj = (player2 *)malloc(sizeof(player2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/player2.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH - 85 - 332;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->hp = 4;
    pDerivedObj->state = P2_nothing;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = player2_update;
    pObj->Interact = player2_interact;
    pObj->Draw = player2_draw;
    pObj->Destroy = player2_destory;
    printf("correct player2 hp: %d\n", (pDerivedObj->hp));
    printf("player2_init_finish\n");
    return pObj;
}
void player2_update(Elements *self) {
     player2 *p2 = ((player2 *)(self->pDerivedObj));
    if(state == P2_turn_L){
        if(key_state[ALLEGRO_KEY_1]){
            //shoot him self
            if(bullet_arr[bullet_num-1]==1){
                p2->state = P2_Shoot_P1;
                bullet_num = bullet_num - 1;
            }else{
                p2->state = P2_Blank_p1;
                bullet_num = bullet_num - 1;
            }
        }else if(key_state[ALLEGRO_KEY_2]){
            //shoot myself
            if(bullet_arr[bullet_num-1]==1){
                p2->state = P2_Shoot_P2;
                bullet_num = bullet_num - 1;
            }else{
                p2->state = P2_Blank_p2;
                bullet_num = bullet_num - 1;
            }
        }else{
            p2->state = P2_nothing;
            
        }
    }
}
void player2_interact(Elements *self, Elements *tar) {}
void player2_draw(Elements *self)
{
    player2 *Obj = ((player2 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}


void player2_destory(Elements *self)
{
    player2 *Obj = ((player2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
