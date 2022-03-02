#include "GameManager.h"
#include "SHOTGUN.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;

SHOTGUN::SHOTGUN(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/SHOTGUN_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/SHOTGUN_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/SHOTGUN.png"));

	cool_time = 6.0f;

	this->angle = angle;
	r = 4;

	sound = GMp->loadSoundMem("sound/shot.mp3");
	ChangeVolumeSoundMem(255 * 0.4, sound);

	//=============================================================================
	//�f�o�b�O�p

	if (!GameManager::DEBUG_MODE) { return; }

	cool_time = 6.0f;

	//=============================================================================
}


//----------------------------------------------------------------------------------------------
//�A�N�e�B�u

void SHOTGUN::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p){

	pos_b = pos;
	dire = { dire_x,dire_y };
	_team = p->_team;

	_active = true;
	_effect = true;

	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}


//----------------------------------------------------------------------------------------------
//�X�L���̏I���

void SHOTGUN::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void SHOTGUN::Skill_UpDate(float deltatime) {

	if (!_active || !_effect)return;

	int deg = rand() % 60 - 30;
	float rad = tpr::Angle::DegChangeRad(deg);

	tpr::Vector2 dire_ = tpr::Rotation::RotaVec2(dire, { 0,0 }, rad);

	GMp->SPp->MakeBullet(pos_b, dire_, skill_img[0], _team, speed, scope, r);

	flame_count++;

	if (flame_count > 6) {

		_effect = false;
		flame_count = 0;
	}
}
void SHOTGUN::Skill_Render(Camera* cam) {

	if (!_effect) { return; }


}