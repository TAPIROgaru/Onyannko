#include "NINTOU.h"
#include "../GameManager.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "../TPRlib/tpr_library.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
NINTOU::NINTOU(tpr::Vector2 pos_, tpr::Vector2 dire_, bool _team_) {

	pos = (pos_.x, pos_.y, 0);
	dire = dire_;
	_team = _team_;
	angle = tpr::Angle::RadCalc(tpr::Vector2(), dire_);

	if (dire_.x < 0) {
		angle += tpr::Angle::DegChangeRad(-90);
	}
	else if (dire_.x > 0) {
		angle += tpr::Angle::DegChangeRad(90);
	}

	img = GMp->loadGraph("graphics/NINGU/Slash.png");

	size_w = size_x;
	size_h = size_y;
}


//---------------------------------------------------------------------------------------------------
//動かす
void NINTOU::Move(float deltatime) {

	if (GMp->SRp->_switch) { return; }

	pos.x += dire.x * speed;
	pos.y += dire.y * speed;

	count += deltatime;
}

//---------------------------------------------------------------------------------------------------
//消す
bool NINTOU::isDelete() {

	if (pos.x > GMp->TILE_VALUE_W * GMp->TILE_SIZE_W) { return true; }
	if (pos.x < size_w >> 1) { return true; }

	if (pos.y > GMp->TILE_VALUE_H * GMp->TILE_SIZE_H) { return true; }
	if (pos.y < size_h >> 1) { return true; }

	if (scope < count) { return true; }

	return false;
}


//---------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void NINTOU::Update(float deltatime) {

	if (!GMp->SPp->_switch && !GMp->SRp->_switch) { alive_flag = false; }

	exrate += deltatime;
	size_w = exrate * size_x;
	size_h = exrate * size_y;
}
void NINTOU::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, exrate, angle, img, true);
}