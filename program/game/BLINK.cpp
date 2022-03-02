#include "GameManager.h"
#include "PlayScene.h"
#include "BLINK.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------
//�R���X�g���N�^

BLINK::BLINK(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/BLINK_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/BLINK_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/BLINK.png"));

	cool_time = 4.0f;
	this->angle = angle;

	sound = GMp->loadSoundMem("sound/blink.mp3");
	ChangeVolumeSoundMem((int)(255 * 0.4), sound);

	//=============================================================================
	//�f�o�b�O�p

	if (!GameManager::DEBUG_MODE) { return; }

	cool_time = 6.0f;

	//=============================================================================
}


//----------------------------------------------------------------------------------------------
//�A�N�e�B�u

void BLINK::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{
	this->pos_b = pos;
	p->pos.x += dire_x * move_amount;
	p->pos.y += dire_y * move_amount;

	_active = true;
	_effect = true;

	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}


//----------------------------------------------------------------------------------------------
//�X�L���̏I���

void BLINK::TurnOff(float deltatime) {

	count += deltatime;
	if (count > 0.5f) {
		_effect = false;
		count = 0.0f;
	}
}


//----------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void BLINK::Skill_UpDate(float deltatime) {

	if (!_active) { return; }

	TurnOff(deltatime);
	
}
void BLINK::Skill_Render(Camera* cam) {

	if (!_effect) { return; }

	tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(pos_b);
	DrawRotaGraph((int)pos_.x, (int)pos_.y, 1.0, 0, skill_img[0], true);
}