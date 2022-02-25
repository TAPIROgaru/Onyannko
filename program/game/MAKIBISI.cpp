#include "GameManager.h"
#include "MAKIBISI.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;


MAKIBISI::MAKIBISI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/MAKIBISI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/MAKIBISI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/MAKIBISI.png"));

	cool_time = 0.0f;
	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void MAKIBISI::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void MAKIBISI::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void MAKIBISI::Skill_UpDate(float deltatime) {

}
void MAKIBISI::Skill_Render(Camera* cam) {


}