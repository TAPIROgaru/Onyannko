#include "MAKIBISI.h"
#include "../GameManager.h"
#include "../PlayScene.h"
#include "../ResultScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
MAKIBISI::MAKIBISI(t2k::Vector3 pos_, bool _team_) {

	pos = pos_;
	_team = _team_;

	img = GMp->loadGraph("graphics/NINGU/MAKIBISI.png");
}


//---------------------------------------------------------------------------------------------------
//
bool MAKIBISI::isHit() {

	//キャラの位置
	tpr::Vector2 pos_ = GMp->SPp->GetCharaPosition(!_team);
	t2k::Vector3 _pos_ = { pos_.x, pos_.y, 0 };

	//まきびし内のキャラに近い位置
	t2k::Vector3 pos__ = t2k::getNearestRectPoint(pos, size_x, size_y, _pos_);

	if (GMp->SPp->isHit_DotAndCircle(pos__, _pos_, 16)) {

		GMp->SPp->Slow(!_team, speed);
		GMp->SPp->Damage(!_team, damege);

		return true;
	}

	return false;
}


//---------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void MAKIBISI::Update(float deltatime) {

	if (isHit()) {
		alive_flag = false;
	}
	else if (count > scope) {
		alive_flag = false;
	}

	count += deltatime;
	if (!GMp->SPp->_switch && !GMp->SRp->_switch) { alive_flag = false; }
}
void MAKIBISI::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, 0, img, true);
}