#include "Bullet.h"
#include "GameManager.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Bullet::Bullet(float x, float y, float dire_x, float dire_y, float a) {

	pos = { x,y,0 };

	direction_x = dire_x;
	direction_y = dire_y;
	angle = a;
}


//----------------------------------------------------------------------------------------------------
//������
void Bullet::Move() {

	pos.x += direction_x * speed;
	pos.y += direction_y * speed;
}

//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void Bullet::Update(float deltatime) {

	Move();
}
void Bullet::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->FixPositionVector(pos);
	DrawCircle(pos_.x, pos_.y, 5, -1, false);
}

//----------------------------------------------------------------------------------------------------