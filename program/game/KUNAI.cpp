#include "GameManager.h"
#include "KUNAI.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;


KUNAI::KUNAI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KUNAI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KUNAI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KUNAI.png"));

	cool_time = 10.0f;
	this->angle = angle;

	sound = GMp->loadSoundMem("sound/shuriken.mp3");
	ChangeVolumeSoundMem((int)(255 * 0.4), sound);

	//=============================================================================
	//デバッグ用

	if (!GameManager::DEBUG_MODE) { return; }

	cool_time = 6.0f;

	//=============================================================================
}


//----------------------------------------------------------------------------------------------
//アクティブ

void KUNAI::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{
	this->pos_b = pos;

	dire = tpr::Vector2(dire_x, dire_y);

	_team = p->_team;

	_active = true;
	_effect = true;

	r = 14;
	prev_pos = { 0,0,0 };

	damage += p->sta.attack;

	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void KUNAI::TurnOff(float deltatime) {

	count += deltatime;

	if (count > 0.4f) {
		_effect = false;
		count = 0.0f;
	}
}


//----------------------------------------------------------------------------------------------
//敵と弾同士の当たり判定

void KUNAI::isHit() {

	int num;

	if (GMp->SPp->isHit_Wall(t2k::Vector3{ pos_b.x,pos_b.y,0 }, prev_pos, (float)r, &num)) {


		if (num == 0 || num == 2) {
			dire.y *= -1;
			prev_pos.y += dire.y * r;
		}
		if (num == 3 || num == 1) {
			dire.x *= -1;
			prev_pos.x += dire.x * r;
		}

		pos_b = { prev_pos.x, prev_pos.y };
		count = 0.0f;
	}

	if (isHit_Bullet()) {
		hitpoint--;
	}

	if (isHit_Enemy(pos_b)) {

		if (_team) {
			GMp->SPp->Ep->sta.hp_ -= damage;
		}
		else if (_team) {
			GMp->SPp->Pp->sta.hp_ -= damage;
		}

		count = 999.0f;
	}

}


//----------------------------------------------------------------------------------------------
//動く

void KUNAI::Move() {

	pos_b.x += dire.x * speed;
	pos_b.y += dire.y * speed;

	isHit();

	prev_pos = { pos_b.x,pos_b.y,0 };
}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void KUNAI::Skill_UpDate(float deltatime) {

	if (!_active || !_effect)return;

	TurnOff(deltatime);

	Move();
}
void KUNAI::Skill_Render(Camera* cam) {

	if (!_effect) { return; }

	float rad = tpr::Angle::RadCalc(tpr::Vector2(0, 0), dire);
	tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(pos_b);

	DrawRotaGraph((int)pos_.x, (int)pos_.y, 1, rad, skill_img[0], true);

	hp.DrawGauge(tpr::Vector2(pos_.x, pos_.y - 17), 0, (float)MAX_HP, (float)hitpoint);
}