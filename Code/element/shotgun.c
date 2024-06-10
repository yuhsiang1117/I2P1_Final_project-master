#include "shotgun.h"
#include "../shapes/Rectangle.h"
/*
   [shotgun function]
*/
Elements *New_shotgun(int label)
{
    shotgun *pDerivedObj = (shotgun *)malloc(sizeof(shotgun));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/shotgun.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 105;
    pDerivedObj->state = unused;
    pDerivedObj->y = HEIGHT - pDerivedObj->height + 20;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = shotgun_update;
    pObj->Interact = shotgun_interact;
    pObj->Draw = shotgun_draw;
    pObj->Destroy = shotgun_destory;
    return pObj;
}
void shotgun_update(Elements *self) {
    shotgun *sgun = ((shotgun *)(self->pDerivedObj));
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    // printf("%d\n", state);
    if(state == P1_turn_L || state == P2_turn_L){
        if(mouse_x >= sgun->x && mouse_x <= sgun->x+sgun->width && mouse_y >= sgun->y && mouse_y <= sgun->y+sgun->height && ev.mouse.button == 1){
            printf("shotgun_presssed\n");
            shot_state = 1;
        }
    }
}

void shotgun_interact(Elements *self, Elements *tar) {}
void shotgun_draw(Elements *self)
{
    shotgun *Obj = ((shotgun *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);

}
void shotgun_destory(Elements *self)
{
    shotgun *Obj = ((shotgun *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
