#include "GameManager.h"
#include "SHOTGUN.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;

SHOTGUN::SHOTGUN(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/SHOTGUN_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/SHOTGUN_open.png");

	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void SHOTGUN::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void SHOTGUN::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void SHOTGUN::Skill_UpDate(float deltatime) {

}
void SHOTGUN::Skill_Render(Camera* cam) {


}