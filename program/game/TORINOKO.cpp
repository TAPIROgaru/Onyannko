#include "GameManager.h"
#include "TORINOKO.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayScene.h"

extern GameManager* GMp;


TORINOKO::TORINOKO(tpr::Vector2 pos_, int angle) {

	std::vector<std::string> str;

	str.emplace_back("graphics/NINGU/TORINOKO.png");
	str.emplace_back("graphics/NINGU/TORINOKO2.png");
	str.emplace_back("graphics/NINGU/TORINOKO3.png");
	str.emplace_back("graphics/NINGU/TORINOKO4.png");
	str.emplace_back("graphics/NINGU/TORINOKO5.png");
	str.emplace_back("graphics/NINGU/TORINOKO6.png");
	str.emplace_back("graphics/NINGU/TORINOKO7.png");
	str.emplace_back("graphics/NINGU/TORINOKO8.png");

	skill_img = GMp->loadDivGraph(str, 8);

	scroll_img_close = GMp->loadGraph("graphics/scroll/TORINOKO_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/TORINOKO_open.png");

	cool_time = 0.0f;
	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//�A�N�e�B�u

void TORINOKO::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{


	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//�X�L���̏I���

void TORINOKO::TurnOff(float deltatime) {

}


//----------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void TORINOKO::Skill_UpDate(float deltatime) {

}
void TORINOKO::Skill_Render(Camera* cam) {


}