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
//コンストラクタ
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
Scroll::Scroll(int num, int angle, tpr::Vector2 pos) {

	my_number = num;

	tpr::Vector2 pos_(pos.x, pos.y - 50);

	pos_= Rotation::RotaVec2(pos_, pos, Angle::DegChangeRad(angle));

	make_skill_func[my_number](this, pos_, angle);
}


//------------------------------------------------------------------------------------------------
//発動
void Scroll::Activate(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	skill_func[my_number](this, pos, dire_x, dire_y, p);
}


//------------------------------------------------------------------------------------------------
//かぎなわ　(引っ張る)
void Scroll::Kaginawa(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if (kaginawa->_active)return;
	kaginawa->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Kaginawa(tpr::Vector2 pos, int angle) {

	kaginawa = new KAGINAWA(pos, angle);
	skill_p.emplace_back(kaginawa);
}


//------------------------------------------------------------------------------------------------
//にんとう　(三回)
void Scroll::Nintou(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(nintou->_active)return;
	nintou->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Nintou(tpr::Vector2 pos, int angle) {

	nintou = new NINTOU(pos, angle);
	skill_p.emplace_back(nintou);
}


//------------------------------------------------------------------------------------------------
//とりのこ　(ばくだん)
void Scroll::Torinoko(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(torinoko->_active)return;
	torinoko->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Torinoko(tpr::Vector2 pos, int angle) {

	torinoko = new TORINOKO(pos, angle);
	skill_p.emplace_back(torinoko);
}


//------------------------------------------------------------------------------------------------
//かくれみ　(半透明にする)
void Scroll::Kakuremi(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(kakuremi->_active)return;
	kakuremi->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Kakuremi(tpr::Vector2 pos, int angle) {

	kakuremi = new KAKUREMI(pos, angle);
	skill_p.emplace_back(kakuremi);
}


//------------------------------------------------------------------------------------------------
//くない　ついせき(相殺あり)
void Scroll::Kunai(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(kunai->_active)return;
	kunai->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Kunai(tpr::Vector2 pos, int angle) {

	kunai = new KUNAI(pos, angle);
	skill_p.emplace_back(kunai);
}


//------------------------------------------------------------------------------------------------
//ブリンク
void Scroll::Blink(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(blink->_active)return;
	blink->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Blink(tpr::Vector2 pos, int angle) {

	blink = new BLINK(pos, angle);
	skill_p.emplace_back(blink);
}


//------------------------------------------------------------------------------------------------
//散弾
void Scroll::Shotgun(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(shotgun->_active)return;
	shotgun->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Shotgun(tpr::Vector2 pos, int angle) {

	shotgun = new SHOTGUN(pos, angle);
	skill_p.emplace_back(shotgun);
}


//------------------------------------------------------------------------------------------------
//まきびし　(トラップ)
void Scroll::Makibisi(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(makibisi->_active)return;
	makibisi->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Makibisi(tpr::Vector2 pos, int angle) {

	makibisi = new MAKIBISI(pos, angle);
	skill_p.emplace_back(makibisi);
}


//------------------------------------------------------------------------------------------------
//徹甲弾
void Scroll::Teppo(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p) {

	if(teppo->_active)return;
	teppo->Active(pos, dire_x, dire_y, p);
}
void Scroll::make_Teppo(tpr::Vector2 pos, int angle) {

	teppo = new TEPPO(pos, angle);
	skill_p.emplace_back(teppo);
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

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
void Scroll::RenderDebug(Camera* cam) {

	for (auto p : skill_p) {
		p->Skill_RenderDebug(cam);
	}
}