#include "GameManager.h"
#include "TEPPO.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;

TEPPO::TEPPO(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/TEPPO_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/TEPPO_open.png");

	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void TEPPO::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void TEPPO::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void TEPPO::Skill_UpDate(float deltatime) {

}
void TEPPO::Skill_Render(Camera* cam) {


}