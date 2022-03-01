#include "GameManager.h"
#include "TEPPO.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;

TEPPO::TEPPO(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/TEPPO_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/TEPPO_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/TEPPO.png"));

	cool_time = 6.0f;

	this->angle = angle;
	r = 14;

	//=============================================================================
	//�f�o�b�O�p

	if (!GameManager::DEBUG_MODE) { return; }

	cool_time = 6.0f;

	//=============================================================================
}


//----------------------------------------------------------------------------------------------
//�A�N�e�B�u

void TEPPO::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p){

	dire = { dire_x,dire_y };
	_team = p->_team;

	if (_team) { e_p = GMp->SPp->Ep; }
	else if (!_team) { e_p = GMp->SPp->Pp; }

	_active = true;
	_effect = true;

	bp = GMp->SPp->MakeBullet(pos, dire, skill_img[0], _team, speed, scope, r);

	pos_b = { bp->pos.x, bp->pos.y };
}


//----------------------------------------------------------------------------------------------
//�X�L���̏I���

void TEPPO::TurnOff(float deltatime) {

	count += deltatime;

	if (count > scope - 0.01f) {
		_effect = false;
		count = 0.0f;
	}
}


//----------------------------------------------------------------------------------------------
//�����蔻��
void TEPPO::isHit() {

	isHit_Bullet();

	if (isHit_Enemy(pos_b)) {
		e_p->sta.hp_ -= damage;
	}
}


//----------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void TEPPO::Skill_UpDate(float deltatime) {

	if (!_active || !_effect)return;

	pos_b = { bp->pos.x, bp->pos.y };

	isHit();
	TurnOff(deltatime);
}
void TEPPO::Skill_Render(Camera* cam) {

	if (!_effect) { return; }


}