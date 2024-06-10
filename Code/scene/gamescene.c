#include "gamescene.h"
#include <time.h>
#include "../element/player1.h"
#include "../element/player2.h"
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
    _Register_elements(pObj, New_Key(Key_L));
    _Register_elements(pObj, New_Magnifier(Magnifier_L));
    _Register_elements(pObj, New_Handcuff(Handcuff_L));
    _Register_elements(pObj, New_player1(Player1_L));
    _Register_elements(pObj, New_player2(Player2_L));
    //_Register_elements(pObj, New_Chest(Chest_L));
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    
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
    // printf("stop at here\n");
    // printf("%d\n", pl1->hp);
    // printf("%d\n", pl2->hp);
    srand((unsigned)time(&t));
    //printf("STATE:%d\n", state);
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
            for(int i=0;i<6;i++){
                p1item += p1->item[i];
            }
            srand(time(0));
            for(int i=0;i<4;i++){
                if(p1item>=6) break;
                int nowitem;
                //nowitem = Chest_drawitem();
                nowitem = rand()%31;
                nowitem %= 6;
                p1->item[nowitem]++;
                p1item++;
                printf("%d ",nowitem);
            }
            printf("\n");
            printf("player1 has 1=%d 2=%d 3=%d 4=%d 5=%d 6=%d\n",p1->item[0],p1->item[1],p1->item[2],p1->item[3],p1->item[4],p1->item[5]);
            int p2item = 0;
            for(int i=0;i<6;i++){
                p2item += p2->item[i];
            }
            srand(time(0));
            for(int i=0;i<4;i++){
                if(p2item>=6) break;
                int nowitem;
                //nowitem = Chest_drawitem();
                nowitem = rand()%17;
                nowitem %= 6;
                p2->item[nowitem]++;
                p2item++;
                printf("%d ",nowitem);
            }
            printf("\n");
            printf("player2 has 1=%d 2=%d 3=%d 4=%d 5=%d 6=%d\n",p2->item[0],p2->item[1],p2->item[2],p2->item[3],p2->item[4],p2->item[5]);
            state = P1_turn_L;
            break;
        case P1_turn_L:
            if(pl1->state == Shoot_P1){
                pl1->hp = pl1->hp - 1;
                pl1->state = nothing;
                state = P2_turn_L;
            }else if(pl1->state == Shoot_P2){
                pl2->hp = pl2->hp - 1;
                pl1->state = nothing;
                state = P2_turn_L;
            }else if(pl1->state == Blank_p1){
                pl1->state = nothing;
                state = P1_turn_L;
            }else if(pl1->state == Blank_p2){
                pl1->state = nothing;
                state = P2_turn_L;
            }else if(bullet_num <= 0){
                pl1->state = nothing;
                state = Reset_L;
            }else{
                state = state;
            }
            break;

        case P2_turn_L:
            if(pl2->state == P2_Shoot_P2){
                pl2->state = P2_nothing;
                pl2->hp = pl2->hp - 1;
                state = P1_turn_L;
            }else if(pl2->state == P2_Shoot_P1){
                pl2->state = P2_nothing;
                pl1->hp = pl1->hp - 1;
                state = P1_turn_L;
            }else if(pl1->state == P2_Blank_p2){
                pl2->state = P2_nothing;
                state = P2_turn_L;
            }else if(pl1->state == P2_Blank_p1){
                pl2->state = P2_nothing;
                state = P1_turn_L;
            }else if(bullet_num <= 0){
                pl2->state = P2_nothing;
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
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 125, 0, ALLEGRO_ALIGN_CENTRE, "Player 1");
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 925, 0, ALLEGRO_ALIGN_CENTRE, "Player 2");
    // printf("game scene drawing2\n");
    // printf("%d\n", pl1->hp);
    // printf("%d\n", pl2->hp);
    int pl1_x = 200;
    int pl2_x = 600;
    if(pl1->hp == 4){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl1_x, 150, ALLEGRO_ALIGN_CENTRE, "4");
    }else if(pl1->hp == 3){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl1_x, 150, ALLEGRO_ALIGN_CENTRE, "3");
    }else if(pl1->hp == 2){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl1_x, 150, ALLEGRO_ALIGN_CENTRE, "2");
    }else if(pl1->hp == 1){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl1_x, 150, ALLEGRO_ALIGN_CENTRE, "1");
    }else{
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl1_x, 150, ALLEGRO_ALIGN_CENTRE, "0");
    }
    // printf("game scene drawing3\n");
    if(pl2->hp == 4){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "4");
    }else if(pl2->hp == 3){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "3");
    }else if(pl2->hp == 2){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "2");
    }else if(pl2->hp == 1){
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "1");
    }else{
        al_draw_text(gs->font, al_map_rgb(255, 0, 0), pl2_x, 150, ALLEGRO_ALIGN_CENTRE, "0");
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
