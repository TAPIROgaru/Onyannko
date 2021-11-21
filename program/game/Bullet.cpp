#include "Bullet.h"
#include "GameManager.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Bullet::Bullet(float x, float y, float dire_x, float dire_y, bool t) {

	pos = { x,y,0 };

	direction_x = dire_x;
	direction_y = dire_y;

	img = GMp->loadGraph("graphics/shuriken.png");

	_team = t;
	r = 7;
}


//----------------------------------------------------------------------------------------------------
//������
void Bullet::Move() {

	if (isDelete()) {
		alive_flag = false;
		return;
	}

	if (GMp->SRp->_switch) { return; }

	pos.x += direction_x * speed;
	pos.y += direction_y * speed;
}


//----------------------------------------------------------------------------------------------------
//����
bool Bullet::isDelete() {

	if (pos.x > GMp->FIELD_W) { return true; }
	if (pos.x < -GMp->FIELD_W) { return true; }

	if (pos.y > GMp->FIELD_H) { return true; }
	if (pos.y < -GMp->FIELD_H) { return true; }


	return false;
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��
void Bullet::Update(float deltatime) {

	Move();

	if (GMp->SRp->_switch) { alive_flag = false; }
}
void Bullet::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, angle, img, 1);

	angle += 0.15f;
}

//----------------------------------------------------------------------------------------------------