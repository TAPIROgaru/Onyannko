#include "Square.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Square::Square(t2k::Vector3 start, int img) {

	pos = start;
	this->img = img;
	quad = new tpr::Quadrilateral(tpr::Vector2(start.x, start.y), size_w_, size_h_);
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void Square::Update(float deltatime) {

	if (GMp->SRp->_switch && GMp->SRp->_switch) { alive_flag = false; }
}

void Square::Render(Camera* camera) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawGraph((int)pos_.x, (int)pos_.y, img, false);

	//==================================================================
	//デバッグ用
	//tpr::Quadrilateral(tpr::Vector2(pos_.x, pos_.y), 
	//	tpr::Vector2(pos_.x-size_w_, pos_.y - size_h_)).DrawBox(-1);
	//==================================================================
}


//----------------------------------------------------------------------------------------------------