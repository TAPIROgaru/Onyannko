#include "NINTOU.h"
#include "GameManager.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;

NINTOU::NINTOU(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/NINTOU_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/NINTOU_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/NINTOU1.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/NINTOU2.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/NINTOU3.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/NINTOU4.png"));

	cool_time = 8.0f;
	this->angle = angle;
	r = 23;
}

void NINTOU::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	p_p = p;
	_team = p->_team;
	if (_team) { e_p = GMp->SPp->Ep; }
	else if (!_team) { e_p = GMp->SPp->Pp; }

	dire = { dire_x,dire_y };
	pos_b = { p_p->pos.x + dire.x * 30,p_p->pos.y + dire.y * 30 };
	origin_defense = p->sta.defense;

	p->sta.defense *= 2;

	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void NINTOU::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void NINTOU::Skill_UpDate(float deltatime) {

	if (!_active || !_effect)return;

	if (isHit_Enemy(pos_b)) {
		e_p->sta.hp_--;
	}

	if (_move) { 
		p_p->pos += t2k::Vector3{ dire.x,dire.y,0 }*moving_distance;

		pos_b = { p_p->pos.x + dire.x * 30,p_p->pos.y + dire.y * 30 };
		_move = false;
	}

	if (_end_effect) {

		p_p->sta.defense = origin_defense;
		_effect = false;
		_end_effect = false;
		flame_count = 0;
	}
}
void NINTOU::Skill_Render(Camera* cam) {

	if (!_effect) { return; }

	flame_count++;

	tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(pos_b);
	float rad = tpr::Angle::RadCalc({ 0,0 }, dire);

	const int PLAY_IMG_TIMES = 5;

	if (flame_count < PLAY_IMG_TIMES) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, rad, skill_img[0], true);
	}
	else if (flame_count < PLAY_IMG_TIMES * 2) {
		_move = true;
		DrawRotaGraph(pos_.x, pos_.y, 1.5, rad, skill_img[1], true);
	}
	else if (flame_count < PLAY_IMG_TIMES * 3) {
		_move = true;
		DrawRotaGraph(pos_.x, pos_.y, 1.5, rad, skill_img[2], true);
	}
	else if (flame_count < PLAY_IMG_TIMES * 4) {
		_move = true;
		DrawRotaGraph(pos_.x, pos_.y, 1.5, rad, skill_img[3], true);
	}
	else {
		_end_effect = true;
	}
}