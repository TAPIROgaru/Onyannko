#include "GameManager.h"
#include "MAKIBISI.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;


MAKIBISI::MAKIBISI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/MAKIBISI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/MAKIBISI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/MAKIBISI.png"));

	cool_time = 15.0f;
	this->angle = angle;

	r = 15;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void MAKIBISI::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{
	pos_b = pos;
	_team = p->_team;

	if (_team) { e_p = GMp->SPp->Ep; }
	else if (!_team) { e_p = GMp->SPp->Pp; }

	origin_speed = e_p->sta.move_speed;

	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void MAKIBISI::TurnOff(float deltatime) {

	if (!_hit) { return; }

	count += deltatime;

	if (count > 1.5f) {

		count = 0.0f;
		e_p->sta.move_speed = origin_speed;
		_hit = false;
	}
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void MAKIBISI::isHit() {

	if (isHit_Enemy(pos_b)) {

		e_p->sta.hp_--;
		e_p->sta.move_speed *= 0.6f;
		_effect = false;
		_hit = true;
	}
}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void MAKIBISI::Skill_UpDate(float deltatime) {

	if (!_active ) { return; }

	TurnOff(deltatime);

	if (!_effect) { return; }

	isHit();

}
void MAKIBISI::Skill_Render(Camera* cam) {

	if (!_effect) { return; }

	tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(pos_b);
	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, skill_img[0], true);
}