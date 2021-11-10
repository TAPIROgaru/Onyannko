#include "Bullet.h"
#include "GameManager.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Bullet::Bullet(float x, float y, float dire_x, float dire_y, float a, bool t) {

	pos = { x,y,0 };

	direction_x = dire_x;
	direction_y = dire_y;
	angle = a;

	_team = t;
	r = 5;
}


//----------------------------------------------------------------------------------------------------
//動かす
void Bullet::Move() {

	if (isDelete()) {
		alive_flag = false;
		return;
	}

	pos.x += direction_x * speed;
	pos.y += direction_y * speed;
}


//----------------------------------------------------------------------------------------------------
//消す
bool Bullet::isDelete() {

	if (pos.x > GMp->FIELD_W) { return true; }
	if (pos.x < -GMp->FIELD_W) { return true; }

	if (pos.y > GMp->FIELD_H) { return true; }
	if (pos.y < -GMp->FIELD_H) { return true; }


	return false;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void Bullet::Update(float deltatime) {

	Move();
}
void Bullet::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);
	DrawCircle(pos_.x, pos_.y, r, -1, false);
}

//----------------------------------------------------------------------------------------------------