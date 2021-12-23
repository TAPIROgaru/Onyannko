#include "KUNAI.h"
#include "../GameManager.h"
#include "../PlayScene.h"
#include "../ResultScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
KUNAI::KUNAI(tpr::Vector2 pos_, tpr::Vector2 dire_, bool _team_) {

	pos = (pos_.x, pos_.y, 0);
	dire = dire_;
	_team = _team_;

	img = GMp->loadGraph("graphics/NINGU/Slash.png");
}


//---------------------------------------------------------------------------------------------------
//������
void KUNAI::Move(float deltatime) {

	if (GMp->SRp->_switch) { return; }

	pos.x += dire.x * speed;
	pos.y += dire.y * speed;

	count += deltatime;
}

//---------------------------------------------------------------------------------------------------
//����
bool KUNAI::isDelete() {

	if (pos.x > GMp->TILE_VALUE_W * GMp->TILE_SIZE_W) { return true; }
	if (pos.x < r) { return true; }

	if (pos.y > GMp->TILE_VALUE_H * GMp->TILE_SIZE_H) { return true; }
	if (pos.y < r) { return true; }

	if (scope < count) { return true; }

	return false;
}


//---------------------------------------------------------------------------------------------------
//���t���[���Ăяo��
void KUNAI::Update(float deltatime) {

	if (!GMp->SPp->_switch && !GMp->SRp->_switch) { alive_flag = false; }
}
void KUNAI::Render(Camera* cam) {

}