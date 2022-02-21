#include "Scroll.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "BLINK.h"
#include "KAGINAWA.h"
#include "KAKUREMI.h"
#include "KUNAI.h"
#include "MAKIBISI.h"
#include "NINTOU.h"
#include "SHOTGUN.h"
#include "TEPPO.h"
#include "TORINOKO.h"

extern GameManager *GMp;

using namespace tpr;


//------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Scroll::Scroll(int num, char c, tpr::Vector2 pos_) {

	my_number = num;
	int angle;

	tpr::Vector2 pos__(pos_.x, pos_.y - 50);

	if (c == 'u') {

		angle = 0;
	}
	else if (c == 'a') {

		angle = 120;
		pos__ = Rotation::RotaVec2(pos__, pos_, Angle::DegChangeRad(angle));
	}
	else if (c == 'b') {

		angle = 240;
		pos__ = Rotation::RotaVec2(pos__, pos_, Angle::DegChangeRad(angle));
	}

	make_skill_func[my_number](this, pos__, angle);

	
}


//------------------------------------------------------------------------------------------------
//����
void Scroll::Activate(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	skill_func[my_number](this, pos, dire_x, dire_y, p);
}


//------------------------------------------------------------------------------------------------
//�����Ȃ�@(��������)
void Scroll::Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if (kaginawa->_active)return;
	kaginawa->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Kaginawa(tpr::Vector2 pos, int angle) {

	kaginawa = new KAGINAWA(pos, angle);
	skill_p.emplace_back(kaginawa);
}


//------------------------------------------------------------------------------------------------
//�ɂ�Ƃ��@(�O��)
void Scroll::Nintou(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(nintou->_active)return;
}
void Scroll::make_Nintou(tpr::Vector2 pos, int angle) {

	nintou = new NINTOU(pos, angle);
	skill_p.emplace_back(nintou);
}


//------------------------------------------------------------------------------------------------
//�Ƃ�̂��@(�΂�����)
void Scroll::Torinoko(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(torinoko->_active)return;
}
void Scroll::make_Torinoko(tpr::Vector2 pos, int angle) {

	torinoko = new TORINOKO(pos, angle);
	skill_p.emplace_back(torinoko);
}


//------------------------------------------------------------------------------------------------
//������݁@(�������ɂ���)
void Scroll::Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(kakuremi->_active)return;
}
void Scroll::make_Kakuremi(tpr::Vector2 pos, int angle) {

	kakuremi = new KAKUREMI(pos, angle);
	skill_p.emplace_back(kakuremi);
}


//------------------------------------------------------------------------------------------------
//���Ȃ��@������(���E����)
void Scroll::Kunai(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(kunai->_active)return;
}
void Scroll::make_Kunai(tpr::Vector2 pos, int angle) {

	kunai = new KUNAI(pos, angle);
	skill_p.emplace_back(kunai);
}


//------------------------------------------------------------------------------------------------
//�u�����N
void Scroll::Blink(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(blink->_active)return;
	blink->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Blink(tpr::Vector2 pos, int angle) {

	blink = new BLINK(pos, angle);
	skill_p.emplace_back(blink);
}


//------------------------------------------------------------------------------------------------
//�U�e
void Scroll::Shotgun(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(shotgun->_active)return;
}
void Scroll::make_Shotgun(tpr::Vector2 pos, int angle) {

	shotgun = new SHOTGUN(pos, angle);
	skill_p.emplace_back(shotgun);
}


//------------------------------------------------------------------------------------------------
//�܂��т��@(�g���b�v)
void Scroll::Makibisi(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(makibisi->_active)return;
}
void Scroll::make_Makibisi(tpr::Vector2 pos, int angle) {

	makibisi = new MAKIBISI(pos, angle);
	skill_p.emplace_back(makibisi);
}


//------------------------------------------------------------------------------------------------
//�O�b�e
void Scroll::Teppo(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(teppo->_active)return;
}
void Scroll::make_Teppo(tpr::Vector2 pos, int angle) {

	teppo = new TEPPO(pos, angle);
	skill_p.emplace_back(teppo);
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void Scroll::Update(float deltatime, tpr::Vector2 pos_) {

	for (auto p: skill_p) {
		p->Skill_UpDateMain(deltatime, pos_);
	}
}
void Scroll::Render(Camera* cam) {

	for (auto p : skill_p) {
		p->Skill_RenderMain(cam);
	}
}