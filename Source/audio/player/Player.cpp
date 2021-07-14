#include "DxLib.h"
#include "Player.h"
Player player;

void PlayerMove() {
    

    //playerƒ‚ƒfƒ‹

    {
        DrawCapsule3D(player1, player2,Cap1R, 8,
            GetColor(255,255, 0), GetColor(255, 255, 255), TRUE);
    }
    //enemyƒ‚ƒfƒ‹
    {
        DrawCapsule3D(enemy1, enemy2,Cap2R, 8,
            GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
    }
    DrawFormatString(0, 0, 0xFFFFFF, "%d", player.x);
    DrawFormatString(0, 20, 0xFFFFFF, "%d", player.z);
    DrawFormatString(0, 40, 0xFFFFFF, "%d", player.speed);
    int HitCheck_Capsule_Capsule(VECTOR player1, VECTOR player2, float Cap1R, VECTOR enemy1, VECTOR enemy2, float Cap2R);
    player.x = 0;
    player.z = 0;

    if (g_NowKey & PAD_INPUT_UP || key[KEY_INPUT_UP] == 1)player.z += player.speed;
    if (g_NowKey & PAD_INPUT_DOWN || key[KEY_INPUT_DOWN] == 1)player.z -= player.speed;
    if (g_NowKey & PAD_INPUT_LEFT|| key[KEY_INPUT_LEFT] == 1)player.x -= player.speed;
    if (g_NowKey & PAD_INPUT_RIGHT||key[KEY_INPUT_RIGHT] == 1)player.x += player.speed;

   player3 = VGet(player1.x + player.x, player1.y,player1.z + player.z);
   player4 = VGet(player2.x + player.x, player2.y,player2.z + player.z);
  
    if (HitCheck_Capsule_Capsule(player3, player4, Cap1R,enemy1,enemy2,Cap2R))
    {

    }else {
        
        player1 = player3;
        player2 = player4;
    }
}