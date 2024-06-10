#include "player1.h"
#include "player2.h"
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
    pDerivedObj->damage = 1;
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
    //printf("update p1");
    ElementVec allEle = _Get_all_elements(scene);
    
    Elements *ele_p2 = allEle.arr[Player2_L];
    // int inter_label_p2 = ele_p2->inter_obj[0];
    // ElementVec labelEle_p2 = _Get_label_elements(self, inter_label_p2);
    player2 *p2 = ((player2 *)(ele_p2->pDerivedObj));

    player1 *p1 = ((player1 *)(self->pDerivedObj));
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    // printf("%d\n", state);
    if(state == P1_turn_L){
        if(mouse_x >= p1->x && mouse_x <= p1->x+p1->width && mouse_y >= p1->y && mouse_y <= p1->y+p1->height && ev.mouse.button == 1){
            printf("key_1_presssed_player1\n");
            //shoot my self
            //printf("key1_down\n");
            if(bullet_arr[bullet_num-1]==1){
                p1->state = Shoot_P1;
                bullet_num = bullet_num - 1;
            }else{
                p1->state = Blank_p1;
                bullet_num = bullet_num - 1;
            }
        }else if(mouse_x >= p2->x && mouse_x <= p2->x+p2->width && mouse_y >= p2->y && mouse_y <= p2->y+p2->height && ev.mouse.button == 1){
            printf("key_2_presssed_player1\n");
            //shoot him
            if(bullet_arr[bullet_num-1]==1){
                p1->state = Shoot_P2;
                bullet_num = bullet_num - 1;
            }else{
                p1->state = Blank_p2;
                bullet_num = bullet_num - 1;
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
