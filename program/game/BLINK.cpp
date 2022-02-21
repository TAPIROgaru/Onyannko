#include "GameManager.h"
#include "PlayScene.h"
#include "BLINK.h"
#include "TPRlib/tpr_library.h"
#include "Player.h"
#include "Enemy.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------
//コンストラクタ

BLINK::BLINK(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/BLINK_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/BLINK_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/BLINK.png"));

	cool_time = 10.0f;
	this->angle = angle;
}


//----------------------------------------------------------------------------------------------
//アクティブ

void BLINK::Active(tpr::Vector2 pos, float dire_x, float dire_y, CharaObj* p)
{
	this->pos = pos;
	p->pos.x += dire_x * move_amount;
	p->pos.y += dire_y * move_amount;

	_active = true;
	_effect = true;
}


//----------------------------------------------------------------------------------------------
//スキルの終わり

void BLINK::TurnOff(float deltatime) {

	count += deltatime;
	if (count > 0.5f) {
		_effect = false;
		count = 0.0f;
	}
}


//----------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void BLINK::Skill_UpDate(float deltatime) {

	if (!_active)return;

	TurnOff(deltatime);
	
}
void BLINK::Skill_Render(Camera* cam) {

	if (_effect) {
		tpr::Vector2 pos_ = GMp->SPp->FixPositionVector(pos);
		DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, skill_img[0], true);
	}
}