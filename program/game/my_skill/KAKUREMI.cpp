#include "KAGINAWA.h"
#include "../GameManager.h"
#include "../PlayScene.h"
#include "../ResultScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
KAGINAWA::KAGINAWA(tpr::Vector2 pos_, tpr::Vector2 dire_, bool _team_) {

	pos = (pos_.x, pos_.y, 0);
	dire = dire_;
	_team = _team_;

	img = GMp->loadGraph("graphics/NINGU/Slash.png");
}


//---------------------------------------------------------------------------------------------------
//動かす
void KAGINAWA::Move(float deltatime) {

	if (GMp->SRp->_switch) { return; }

	pos.x += dire.x * speed;
	pos.y += dire.y * speed;

	count += deltatime;
}

//---------------------------------------------------------------------------------------------------
//消す
bool KAGINAWA::isDelete() {

	if (pos.x > GMp->TILE_VALUE_W * GMp->TILE_SIZE_W) { return true; }
	if (pos.x < r) { return true; }

	if (pos.y > GMp->TILE_VALUE_H * GMp->TILE_SIZE_H) { return true; }
	if (pos.y < r) { return true; }

	if (scope < count) { return true; }

	return false;
}


//---------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void KAGINAWA::Update(float deltatime) {

}
void KAGINAWA::Render(Camera* cam) {

}