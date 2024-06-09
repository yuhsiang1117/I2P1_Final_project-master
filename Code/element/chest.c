#include "chest.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
//#include <player2.h>
/*
   [Chest function]
*/
Elements *New_Chest(int label)
{
    Chest *pDerivedObj = (Chest *)malloc(sizeof(Chest));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load Chest images
    char state_string[2][10] = {"appear", "opened"};
    for (int i = 0; i < 2; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chest_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    /*// load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->open_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->open_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->open_Sound, al_get_default_mixer());*/

    // initial the geometric information of Chest
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = WIDTH/2 - pDerivedObj->width/2;
    pDerivedObj->y = HEIGHT/2 - pDerivedObj->height/2;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    // initial the animation component
    pDerivedObj->state = appear;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Chest_draw;
    pObj->Update = Chest_update;
    pObj->Interact = Chest_interact;
    pObj->Destroy = Chest_destory;
    return pObj;
}
void Chest_update(Elements *self)
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    int mouse_x = ev.mouse.x;
    int mouse_y = ev.mouse.y;
    // use the idea of finite state machine to deal with different state
    Chest *che = ((Chest *)(self->pDerivedObj));
    if (che->state == appear)
    {
        if(mouse_x >= che->x && mouse_x <= che->x+che->width && mouse_y >= che->y && mouse_y <= che->y+che->height && ev.mouse.button == 1){
            che->state = opened;
        }
        else{
            che->state = appear;
        }
    }
    else if (che->state == opened){
        if (che->gif_status[che->state]->done){
            printf("Drawing!\n");
            ElementVec allEle = _Get_all_elements(scene);
            Elements* ele = allEle.arr[7];
            player1* p1 = (player1*)ele->pDerivedObj;
            //printf("%d\n",ele->label);
            printf("%d\n",p1->item[0]);
            int p1item = 0;
            for(int i=0;i<6;i++){
                p1item += p1->item[i];
            }
            srand(time(0));
            for(int i=0;i<4;i++){
                if(p1item>=6) break;
                int nowitem;
                //nowitem = Chest_drawitem();
                nowitem = rand()%6;
                p1->item[nowitem]++;
                p1item++;
                printf("%d ",nowitem);
            }
            printf("\n");
            printf("%d\n",p1->item[0]);
            self->dele = true;
        }
    }
}
void Chest_draw(Elements *self)
{
    // with the state, draw corresponding image
    Chest *che = ((Chest *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(che->gif_status[che->state], al_get_time());
    if (frame){
        al_draw_bitmap(frame, che->x, che->y,0);
    }
    /*if (che->state == ATK && che->gif_status[che->state]->display_index == 2)
    {
        al_play_sample_instance(che->atk_Sound);
    }*/
}
void Chest_destory(Elements *self)
{
    Chest *Obj = ((Chest *)(self->pDerivedObj));
    //al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 2; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

int Chest_drawitem(){
    time_t t;
    srand(time(0));
    int index = rand() % 6;
    return index;
}

void Chest_interact(Elements *self, Elements *tar){}
