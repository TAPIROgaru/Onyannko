#include "Bullet.h"
#include "GameManager.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Bullet::Bullet(float x, float y, float dire_x, float dire_y, float a) {

	pos = { x,y,0 };

	direction_x = dire_x;
	direction_y = dire_y;
	angle = a;
}


//----------------------------------------------------------------------------------------------------
//動かす
void Bullet::Move() {

	pos.x += direction_x * speed;
	pos.y += direction_y * speed;
}

//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void Bullet::Update(float deltatime) {

	Move();
}
void Bullet::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->FixPositionVector(pos);
	DrawCircle(pos_.x, pos_.y, 5, -1, false);
}

//----------------------------------------------------------------------------------------------------