#include "Square.h"
#include "GameManager.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Square::Square(t2k::Vector3 start,int img,int type) {

	pos = start;
	this->img = img;
	this->type = type;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void Square::Update(float deltatime) {

	if (GMp->SRp->_switch) { alive_flag = false; }
}

void Square::Render(Camera* camera) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawGraph(pos_.x, pos_.y, img, false);
}


//----------------------------------------------------------------------------------------------------