#include "gamescene.h"
#include <time.h>
#include "../element/player1.h"
#include "../element/player2.h"
#include "sceneManager.h"
#include "../element/shotgun.h"
#include "menu.h"
/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{

    printf("scene_init\n");
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/room.png");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    // _Register_elements(pObj, New_Floor(Floor_L));
    // _Register_elements(pObj, New_Teleport(Teleport_L));
    // _Register_elements(pObj, New_Tree(Tree_L));
    // _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Beer(Beer_L));
    _Register_elements(pObj, New_Table(Table_L));
    _Register_elements(pObj, New_Ciga(Ciga_L));
    _Register_elements(pObj, New_Magnifier(Magnifier_L));
    _Register_elements(pObj, New_Handcuff(Handcuff_L));
    _Register_elements(pObj, New_player1(Player1_L));
    _Register_elements(pObj, New_player2(Player2_L));
    _Register_elements(pObj, New_shotgun(Shotgun_L));
    //_Register_elements(pObj, New_Chest(Chest_L));
    pDerivedObj->font1 = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    pDerivedObj->font2 = al_load_ttf_font("assets/font/pirulen.ttf", 20, 0);
    
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    printf("scene_init_finish\n");
    return pObj;
}
void game_scene_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    //reset
    int i, j, temp;
    time_t t;
    Elements *ele_p1 = allEle.arr[Player1_L];
    // int inter_label_p1 = ele_p1->inter_obj[0];
    // ElementVec labelEle_p1 = _Get_label_elements(self, inter_label_p1);
    player1 *pl1 = ((player1 *)(ele_p1->pDerivedObj));
    
    Elements *ele_p2 = allEle.arr[Player2_L];
    // int inter_label_p2 = ele_p2->inter_obj[0];
    // ElementVec labelEle_p2 = _Get_label_elements(self, inter_label_p2);
    player2 *pl2 = ((player2 *)(ele_p2->pDerivedObj));

    Elements *ele_shotgun = allEle.arr[Shotgun_L];
    shotgun *shot = ((shotgun *)(ele_shotgun->pDerivedObj));
    // printf("stop at here\n");
    // printf("%d\n", pl1->hp);
    // printf("%d\n", pl2->hp);
    srand((unsigned)time(&t));
    //printf("STATE:%d\n", state);
    int pl1_damage = 1;
    int pl2_damage = 1;
    switch (state){
        case Reset_L:
            //抽子彈
            if(bullet_num==0){
                bullet_num = (rand() % 7) + 2;
                true_bullet = (rand() % bullet_num) + 1;
                blank_bullet = bullet_num - true_bullet;
                for(i=0; i<true_bullet; i++){
                    bullet_arr[i] = 1;
                }
                // hide the bullets
                printf("bn:%d  tb:%d  bb:%d\n", bullet_num, true_bullet, blank_bullet);
                for(i=0; i < 10; i++){
                    j = (rand() % bullet_num);
                    temp = bullet_arr[0];
                    bullet_arr[0] = bullet_arr[j];
                    bullet_arr[j] = temp;   
                        for(j=0; j<bullet_num; j++){
                            printf("%d ", bullet_arr[j]);
                        }printf("\n");
                }
                // state = state;
                for(i=0; i<bullet_num; i++){
                    printf("%d ", bullet_arr[i]);
                }printf("\n");
            }
            showbullet = 1;
            //抽道具
            Elements *ches = New_Chest(Chest_L);
            _Register_elements(scene, ches);
            allEle = _Get_all_elements(self);
            for (int i = 0; i < allEle.len; i++)
            {
                allEle.arr[i]->Update(allEle.arr[i]);
            }
            for (int i = 0; i < allEle.len; i++)
            {
                Elements *ele = allEle.arr[i];
                ele->Draw(ele);
            }
            printf("%d  %d\n",allEle.len,Chest_L);
            Elements* ele3 = allEle.arr[Chest_L];
            Chest* chest = (Chest*)ele3->pDerivedObj;
            while(chest->state == appear){
                printf("state = %d\n",chest->state);
                allEle.arr[Chest_L]->Update(allEle.arr[Chest_L]);
                Elements *ele = allEle.arr[Chest_L];
                ele->Draw(ele);
            }
            printf("Drawing!\n");
            Elements* ele1 = allEle.arr[Player1_L];
            Elements* ele2 = allEle.arr[Player2_L];
            player1* p1 = (player1*)ele1->pDerivedObj;
            player2* p2 = (player2*)ele2->pDerivedObj;
            //printf("%d\n",ele->label);
            //printf("%d\n",p1->item[0]);
            int p1item = 0;
            for(int i=0;i<5;i++){
                p1item += p1->item[i];
            }
            srand(time(0));
            for(int i=0;i<4;i++){
                if(p1item>=6) break;
                int nowitem;
                //nowitem = Chest_drawitem();
                nowitem = rand()%31;
                nowitem %= 5;
                p1->item[nowitem]++;
                p1item++;
                printf("%d ",nowitem);
            }
            printf("\n");
            printf("player1 has 1=%d 2=%d 3=%d 4=%d 5=%d\n",p1->item[0],p1->item[1],p1->item[2],p1->item[3],p1->item[4]);
            int p2item = 0;
            for(int i=0;i<5;i++){
                p2item += p2->item[i];
            }
            srand(time(0));
            for(int i=0;i<4;i++){
                if(p2item>=6) break;
                int nowitem;
                //nowitem = Chest_drawitem();
                nowitem = rand()%17;
                nowitem %= 5;
                p2->item[nowitem]++;
                p2item++;
                printf("%d ",nowitem);
            }
            printf("\n");
            printf("player2 has 1=%d 2=%d 3=%d 4=%d 5=%d\n",p2->item[0],p2->item[1],p2->item[2],p2->item[3],p2->item[4]);
            state = P1_turn_L;
            break;
        case P1_turn_L:
            if(shot_state == 1){
                pl1_damage = 2;
            }
            if(cigastate == 1){
                pl1->hp = pl1->hp + 1;
                cigastate = 0;
            }
            if(pl1->state == Shoot_P1){
                pl1->hp = pl1->hp - pl1_damage;
                pl1->state = nothing;
                magnifierstate = 0;
                beerstate = 0;
                state = P2_turn_L;
            }else if(pl1->state == Shoot_P2){
                pl2->hp = pl2->hp - pl1_damage;
                pl1->state = nothing;
                magnifierstate = 0;
                beerstate = 0;
                state = P2_turn_L;
            }
            else if(pl1->state == Blank_p1){
                pl1->state = nothing;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = P1_turn_L;
            }else if(pl1->state == Blank_p2){
                pl1->state = nothing;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = P2_turn_L;
            }else if(bullet_num <= 0){
                pl1->state = nothing;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = Reset_L;
            }else{
                state = state;
            }
            break;

        case P2_turn_L:
            if(shot_state==1){
                pl2_damage = 2;
            }
            if(cigastate == 1){
                pl2->hp = pl2->hp + 1;
                cigastate = 0;
            }
            if(pl2->state == P2_Shoot_P2){
                pl2->state = P2_nothing;
                pl2->hp = pl2->hp - pl2_damage;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = P1_turn_L;
            }else if(pl2->state == P2_Shoot_P1){
                pl2->state = P2_nothing;
                pl1->hp = pl1->hp - pl2_damage;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = P1_turn_L;
            }else if(pl1->state == P2_Blank_p2){
                pl2->state = P2_nothing;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = P2_turn_L;
            }else if(pl1->state == P2_Blank_p1){
                pl2->state = P2_nothing;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = P1_turn_L;
            }else if(bullet_num <= 0){
                pl2->state = P2_nothing;
                shot_state = 0;
                magnifierstate = 0;
                beerstate = 0;
                state = Reset_L;
            }else{
                state = state;
            }
            break;
        
        default:
            state = state;
            break;
    }


    // if(state==Reset_L && bullet_num==0){
        
    //     bullet_num = (rand() % 7) + 2;
    //     true_bullet = (rand() % bullet_num) + 1;
    //     blank_bullet = bullet_num - true_bullet;
    //     state = P1_turn_L;
    //     for(i=0; i<true_bullet; i++){
    //     bullet_arr[i] = 1;
    //     }
    //     printf("bn:%d  tb:%d  bb:%d\n", bullet_num, true_bullet, blank_bullet);
    //     for(i=0; i < 10; i++){
    //         j = (rand() % bullet_num);
    //         temp = bullet_arr[0];
    //         bullet_arr[0] = bullet_arr[j];
    //         bullet_arr[j] = temp;   
    //             for(j=0; j<bullet_num; j++){
    //                 printf("%d ", bullet_arr[j]);
    //             }printf("\n");
    //     }
    //     for(i=0; i<bullet_num; i++){
    //         printf("%d ", bullet_arr[i]);
    //     }printf("\n");
    // } 
    
}


void game_scene_draw(Scene *self)
{   
    ElementVec allEle = _Get_all_elements(self);
    // Elements *ele_p1 = allEle.arr[Player1_L];
    // player1 *pl1 = ((player1 *)(ele_p1->pDerivedObj));
    
    // Elements *ele_p2 = allEle.arr[Player2_L];
    // player2 *pl2 = ((player2 *)(ele_p2->pDerivedObj));
    Elements *ele_p1 = allEle.arr[Player1_L];
    // int inter_label_p1 = ele_p1->inter_obj[0];
    // ElementVec labelEle_p1 = _Get_label_elements(self, inter_label_p1);
    player1 *pl1 = ((player1 *)(ele_p1->pDerivedObj));
    
    Elements *ele_p2 = allEle.arr[Player2_L];
    // int inter_label_p2 = ele_p2->inter_obj[0];
    // ElementVec labelEle_p2 = _Get_label_elements(self, inter_label_p2);
    player2 *pl2 = ((player2 *)(ele_p2->pDerivedObj));
    int i;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_text(gs->font1, al_map_rgb(255, 0, 0), 250, 375, ALLEGRO_ALIGN_CENTRE, "Player 1");
    al_draw_text(gs->font1, al_map_rgb(255, 0, 0), WIDTH-250, 375, ALLEGRO_ALIGN_CENTRE, "Player 2");
    // printf("game scene drawing2\n");
    // printf("%d\n", pl1->hp);
    // printf("%d\n", pl2->hp);
    int pl1_x = 200;
    int pl2_x = 600;
    al_draw_textf(gs->font1, al_map_rgb(255, 0, 0), 96, 50, ALLEGRO_ALIGN_CENTRE, "  = %d", pl1->hp);
    al_draw_textf(gs->font1, al_map_rgb(255, 0, 0), WIDTH-96, 50, ALLEGRO_ALIGN_CENTRE, "%d =  ", pl2->hp);
    // printf("game scene drawing3\n");
    /*if(pl2->hp == 4){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "4");
    }else if(pl2->hp == 3){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "3");
    }else if(pl2->hp == 2){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "2");
    }else if(pl2->hp == 1){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "1");
    }else{
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "0");
    }*/
    //p1 item
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 96, 120+20, ALLEGRO_ALIGN_CENTRE, " x %d",pl1->item[Beer_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 96, 323+5, ALLEGRO_ALIGN_CENTRE, " x %d",pl1->item[Ciga_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 96, 180+5, ALLEGRO_ALIGN_CENTRE, " x %d",pl1->item[Handcuff_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 96, 276, ALLEGRO_ALIGN_CENTRE, " x %d",pl1->item[Magnifier_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 96, 230, ALLEGRO_ALIGN_CENTRE, " x %d",pl1->item[Shotgun_num]);
    //p2 item
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), WIDTH-96, 120+20, ALLEGRO_ALIGN_CENTRE, "%d x ",pl2->item[Beer_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), WIDTH-96, 323+5, ALLEGRO_ALIGN_CENTRE, "%d x ",pl2->item[Ciga_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), WIDTH-96, 180+5, ALLEGRO_ALIGN_CENTRE, "%d x ",pl2->item[Handcuff_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), WIDTH-96, 276, ALLEGRO_ALIGN_CENTRE, "%d x ",pl2->item[Magnifier_num]);
    al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), WIDTH-96, 230, ALLEGRO_ALIGN_CENTRE, "%d x ",pl2->item[Shotgun_num]);

    if(state == P1_turn_L){
        al_draw_text(gs->font1, al_map_rgb(0, 0, 0), WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "P1's turn");
    }
    else if(state == P2_turn_L){
        al_draw_text(gs->font1, al_map_rgb(0, 0, 0), WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "P2's turn");
    }
    else{
        al_draw_text(gs->font1, al_map_rgb(0, 0, 0), WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "Drawing item");
    }
    int space = 0;
    for(i=0; i<bullet_num; i++){
        if(bullet_arr[i]==1){
            al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 300 + 50*space, 100, ALLEGRO_ALIGN_CENTRE, "%d",bullet_arr[i]);
            space++;
        }
    }
    for(i=0; i<bullet_num; i++){
        if(bullet_arr[i]==0){
            al_draw_textf(gs->font2, al_map_rgb(255, 255, 255), 300 + 50*space, 100, ALLEGRO_ALIGN_CENTRE, "%d",bullet_arr[i]);
            space++;
        }
    }

    if(magnifierstate == 1){
        if(bullet_arr[bullet_num-1] == 1){
            al_draw_text(gs->font2, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2-50, ALLEGRO_ALIGN_CENTRE, "This bullet is real.");
        }
        else{
            al_draw_text(gs->font2, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/2-50, ALLEGRO_ALIGN_CENTRE, "This bullet is blank.");
        }
       
    }
    if(beerstate == 1){
        if(bulletout == 1){
            al_draw_text(gs->font2, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/4-50, ALLEGRO_ALIGN_CENTRE, "unloaded a real bullet");
        }
        else{
            al_draw_text(gs->font2, al_map_rgb(255, 255, 255), WIDTH/2, HEIGHT/4-50, ALLEGRO_ALIGN_CENTRE, "unloaded a blank bullet");
        }
    }

    
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
