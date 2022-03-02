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

void KAGINAWA::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{

	dire = tpr::Vector2(dire_x, dire_y);
	tpr::Vector2 pos_(p->pos.x, p->pos.y);
	origin_pos = p->pos;

	line = new tpr::Line(pos_, 
		tpr::Vector2(pos.x + dire.x * throw_speed, pos.y + dire.y * throw_speed));

	this->p = p;

	if (p->_team) {
		e_p = GMp->SPp->Ep;
	}
	else {
		e_p = GMp->SPp->Pp;
	}

	_active = true;
	_effect = true;

	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void KAGINAWA::TurnOff(float deltatime) {

	if(_hit){
		
		tpr::Vector2 v = line->start_pos - line->end_pos;

		if (48.0f * 48.0f > (v.x * v.x) + (v.y * v.y)) {

			_effect = false;
			_hit = false;
			e_p->_stun = false;
			count = 0.0f;
		}
	}
	else {
		count += deltatime;
	}

	if (count > 0.5f) {
		_effect = false;
		count = 0.0f;
	}
}


//----------------------------------------------------------------------------------------------
//当たり判定

bool KAGINAWA::isHit() {

	tpr::Vector2 pos_(e_p->pos.x, e_p->pos.y);

	if (tpr::isHit_CircleAndCircle(line->end_pos, (float)r, pos_, (float)e_p->r)) {
		return true;
	}

	return false;
}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void KAGINAWA::Skill_UpDate(float deltatime) {

	if (!_active || !_effect)return;

	if (_hit || isHit()) {

		e_p->_stun = true;
		_hit = true;

		line->end_pos -= dire * pull_speed;
		e_p->pos.x -= dire.x * pull_speed;
		e_p->pos.y -= dire.y * pull_speed;

		e_p->prev_pos = e_p->pos;
	}
	else {

		line->end_pos += dire * throw_speed;
	}

	TurnOff(deltatime);

	p->pos = origin_pos;
}
void KAGINAWA::Skill_Render(Camera* cam) {

	if (!_effect) { return; }

	tpr::Vector2 s_pos = GMp->SPp->FixPositionVector(line->start_pos);
	tpr::Vector2 e_pos = GMp->SPp->FixPositionVector(line->end_pos);
	DrawLine((int)s_pos.x, (int)s_pos.y, (int)e_pos.x, (int)e_pos.y, 0);

	float rad = tpr::Angle::RadCalc(line->start_pos, line->end_pos);
	tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(line->end_pos);
	DrawRotaGraph((int)pos_.x, (int)pos_.y, 1.0, rad, skill_img[0], true);
}