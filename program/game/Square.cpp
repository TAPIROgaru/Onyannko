#include "Square.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Square::Square(t2k::Vector3 start, int img) {

	pos = start;
	this->img = img;
	quad = new tpr::Quadrilateral(tpr::Vector2(start.x, start.y), size_w_, size_h_);
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��
void Square::Update(float deltatime) {

	if (GMp->SRp->_switch && GMp->SRp->_switch) { alive_flag = false; }
}

void Square::Render(Camera* camera) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawGraph((int)pos_.x, (int)pos_.y, img, false);

	//==================================================================
	//�f�o�b�O�p
	//tpr::Quadrilateral(tpr::Vector2(pos_.x, pos_.y), 
	//	tpr::Vector2(pos_.x-size_w_, pos_.y - size_h_)).DrawBox(-1);
	//==================================================================
}


//----------------------------------------------------------------------------------------------------