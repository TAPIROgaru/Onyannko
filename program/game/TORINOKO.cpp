#include "GameManager.h"
#include "TORINOKO.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;


TORINOKO::TORINOKO(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/TORINOKO_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/TORINOKO_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO2.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO3.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO4.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO5.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO6.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO7.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TORINOKO8.png"));

	cool_time = 8.0f;
	this->angle = angle;
	r = 20;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void TORINOKO::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p){

	pos_b = pos;
	_team = p->_team;

	if (_team) { e_p = GMp->SPp->Ep; }
	else if (!_team) { e_p = GMp->SPp->Pp; }


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void TORINOKO::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void TORINOKO::Skill_UpDate(float deltatime) {

	if (!_active || !_effect)return;

	if (_check && _init) {
		if (isHit_Enemy(pos_b)) {
			e_p->sta.hp_ -= damage;
			_init = false;
		}
	}

	if (_end_effect) {

		_effect = false;
		_end_effect = false;
		_check = false;
		flame_count = 0;
	}
}
void TORINOKO::Skill_Render(Camera* cam) {

	if (!_effect) { return; }

	flame_count++;

	tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(pos_b);

	const int PLAY_IMG_TIMES_F = 30;
	const int PLAY_IMG_TIMES_S = 6;

	if (flame_count < PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[0], true);
	}
	else if (flame_count < PLAY_IMG_TIMES_S + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[1], true);
	}
	else if (flame_count < PLAY_IMG_TIMES_S * 2 + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[2], true);
		_check = true;
	}
	else if (flame_count < PLAY_IMG_TIMES_S * 3 + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[3], true);
	}
	else if (flame_count < PLAY_IMG_TIMES_S * 4 + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[4], true);
	}
	else if (flame_count < PLAY_IMG_TIMES_S * 5 + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[5], true);
	}
	else if (flame_count < PLAY_IMG_TIMES_S * 6 + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[6], true);
	}
	else if (flame_count < PLAY_IMG_TIMES_S * 7 + PLAY_IMG_TIMES_F) {
		DrawRotaGraph(pos_.x, pos_.y, 1.5, 0, skill_img[7], true);
	}
	else {
		_end_effect = true;
	}
}