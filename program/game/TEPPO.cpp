#include "GameManager.h"
#include "TEPPO.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;

TEPPO::TEPPO(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/TEPPO_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/TEPPO_open.png");

	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//�A�N�e�B�u

void TEPPO::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//�X�L���̏I���

void TEPPO::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void TEPPO::Skill_UpDate(float deltatime) {

}
void TEPPO::Skill_Render(Camera* cam) {


}