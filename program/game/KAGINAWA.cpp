#include "GameManager.h"
#include "KAGINAWA.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------
//コンストラクタ

KAGINAWA::KAGINAWA(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KAGINAWA_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KAGINAWA_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAGINAWA.png"));

	cool_time = 10.0f;
	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void KAGINAWA::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{

	dire = tpr::Vector2(dire_x, dire_y);

	line = new tpr::Line(pos, tpr::Vector2(pos.x + dire.x * speed, pos.y + dire.y * speed));

	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void KAGINAWA::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void KAGINAWA::Skill_UpDate(float deltatime) {

	if (!_effect)return;

}
void KAGINAWA::Skill_Render(Camera* cam) {

	if (_effect) {

		line->DrawLine(-1);

		float rad = tpr::Angle::RadCalc(line->start_pos, line->end_pos);
		tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(line->end_pos);
		DrawRotaGraph(pos_.x, pos_.y, 1.0, rad, skill_img[0], true);
	}
}