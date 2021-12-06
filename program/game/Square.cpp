#include "Square.h"
#include "GameManager.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Square::Square(t2k::Vector3 start, int img) {

	pos = start;
	this->img = img;
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��
void Square::Update(float deltatime) {

	if (GMp->SRp->_switch) { alive_flag = false; }
}

void Square::Render(Camera* camera) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawGraph((int)pos_.x, (int)pos_.y, img, false);
}


//----------------------------------------------------------------------------------------------------