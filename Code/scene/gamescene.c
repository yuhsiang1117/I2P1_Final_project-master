#include "gamescene.h"

/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/room.png");
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 36, 0);
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Beer(Beer_L));
    _Register_elements(pObj, New_Ciga(Ciga_L));
    _Register_elements(pObj, New_Key(Key_L));
    //p2 = New_player2(player2_L);
    _Register_elements(pObj, New_player1(player1_L));
    _Register_elements(pObj, New_Table(Table_L));
    _Register_elements(pObj, New_Chest(Chest_L));
    _Register_elements(pObj, New_Magnifier(Magnifier_L));
    _Register_elements(pObj, New_Handcuff(Handcuff_L));
    //_Register_elements(pObj, p2);
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
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
    /*Elements *ele = allEle.arr[player1_L];
    player1* p1 = (player1*)(ele->pDerivedObj);
    printf("%d\n",p1->hp);*/
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}
void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    int x = 1;
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 125, 0, ALLEGRO_ALIGN_CENTRE, "Player 1");
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 925, 0, ALLEGRO_ALIGN_CENTRE, "Player 2");
    ElementVec allEle = _Get_all_elements(self);
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
