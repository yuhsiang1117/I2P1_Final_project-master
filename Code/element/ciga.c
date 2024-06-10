#include "ciga.h"
#include "../shapes/Rectangle.h"
/*
   [Ciga function]
*/
Elements *New_Ciga(int label)
{
    Ciga *pDerivedObj = (Ciga *)malloc(sizeof(Ciga));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/ciga.png");
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
    pObj->Update = Ciga_update;
    pObj->Interact = Ciga_interact;
    pObj->Draw = Ciga_draw;
    pObj->Destroy = Ciga_destory;
    return pObj;
}
void Ciga_update(Elements *self) {
    Ciga *cga = ((Ciga *)(self->pDerivedObj));
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    // printf("%d\n", state);
    if(state == P1_turn_L || state == P2_turn_L){
        if(mouse_x >= cga->x && mouse_x <= cga->x+cga->width && mouse_y >= cga->y && mouse_y <= cga->y+cga->height && ev.mouse.button == 1){
            printf("Ciga_presssed\n");
            ciga_state = 1;
        }
    }
}
void Ciga_interact(Elements *self, Elements *tar) {}
void Ciga_draw(Elements *self)
{   
    Ciga *Obj = ((Ciga *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Ciga_destory(Elements *self)
{
    Ciga *Obj = ((Ciga *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
