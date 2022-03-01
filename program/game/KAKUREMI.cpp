#include "GameManager.h"
#include "KAKUREMI.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------
//コンストラクタ

KAKUREMI::KAKUREMI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KAKUREMI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KAKUREMI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAKUREMI.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAKUREMI1.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAKUREMI2.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAKUREMI3.png"));
	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAKUREMI4.png"));

	cool_time = 8.0f;
	this->angle = angle;

	//=============================================================================
	//デバッグ用

	if (!GameManager::DEBUG_MODE) { return; }

	cool_time = 6.0f;

	//=============================================================================
}


//----------------------------------------------------------------------------------------------
//アクティブ

void KAKUREMI::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{
	change_speed = p->sta.move_speed * 1.8f;
	origin_img = p->chara_handle;
	origin_speed = p->sta.move_speed;

	p->chara_handle = skill_img[0];
	p->sta.move_speed = change_speed;
	p->_invincible = true;

	this->p = p;

	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void KAKUREMI::TurnOff(float deltatime) {

	count += deltatime;

	if (count > 6.0f) {
		count = 0.0f;
		flame_count = 0;

		p->chara_handle = origin_img;
		p->sta.move_speed = origin_speed;
		p->_invincible = false;

		change_speed = 0.0f;
		origin_img = 0;
		origin_speed = 0.0f;
	}
}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void KAKUREMI::Skill_UpDate(float deltatime) {

	if (!_active )return;

	TurnOff(deltatime);

}
void KAKUREMI::Skill_Render(Camera* cam) {

	if (!_effect)return;

	flame_count++;

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(p->pos);

	if (flame_count < 6) {
		DrawRotaGraph(pos_.x, pos_.y, 2, 0, skill_img[1], true);
	}
	else if (flame_count < 12) {
		DrawRotaGraph(pos_.x, pos_.y, 2, 0, skill_img[2], true);
	}
	else if (flame_count < 18) {
		DrawRotaGraph(pos_.x, pos_.y, 2, 0, skill_img[3], true);
	}
	else if (flame_count < 24) {
		DrawRotaGraph(pos_.x, pos_.y, 2, 0, skill_img[4], true);
	}
	else {
		_effect = false;
	}
}