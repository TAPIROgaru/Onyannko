#include "GameManager.h"
#include "KUNAI.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;


KUNAI::KUNAI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KUNAI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KUNAI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KUNAI.png"));

	cool_time = 0.0f;
	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void KUNAI::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void KUNAI::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void KUNAI::Skill_UpDate(float deltatime) {

}
void KUNAI::Skill_Render(Camera* cam) {


}