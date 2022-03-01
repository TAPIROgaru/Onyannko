#include "Bullet.h"
#include "GameManager.h"
#include "PlayScene.h"
#include "ResultScene.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Bullet::Bullet(float x, float y, float dire_x, float dire_y, bool t) {

	pos = { x,y,0 };
	prve_pos = { x,y,0 };

	direction_x = dire_x;
	direction_y = dire_y;

	img = GMp->loadGraph("graphics/NINGU/SHURIKEN.png");

	_team = t;
	r = GMp->BULLET_RADIUS;
}
Bullet::Bullet(tpr::Vector2 pos, tpr::Vector2 dire, int img, bool _team, float speed, float scope,int r) {

	this->pos = { pos.x,pos.y,0 };
	prev_pos = this->pos;

	direction_x = dire.x;
	direction_y = dire.y;

	this->img = img;
	this->_team = _team;
	this->speed = speed;
	this->scope = scope;
	this->r = r;
}



//----------------------------------------------------------------------------------------------------
//動かす
void Bullet::Move(float deltatime) {

	if (GMp->SRp->_switch) { return; }

	pos.x += direction_x * speed;
	pos.y += direction_y * speed;

	count += deltatime;
}


//----------------------------------------------------------------------------------------------------
//消す
bool Bullet::isDelete() {

	if (pos.x > GMp->TILE_VALUE_W * GMp->TILE_SIZE_W) { return true; }
	if (pos.x < r) { return true; }

	if (pos.y > GMp->TILE_VALUE_H * GMp->TILE_SIZE_H) { return true; }
	if (pos.y < r) { return true; }

	if (scope < count) { return true; }

	if (GMp->SPp->isHit_Wall(pos, r)) { return true; }

	return false;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void Bullet::Update(float deltatime) {

	Move(deltatime);

	if (GMp->SRp->_switch) { alive_flag = false; }

	if (isDelete()) { alive_flag = false; }
}
void Bullet::Render(Camera* cam) {

	t2k::Vector3 pos_ = GMp->SPp->FixPositionVector(pos);

	DrawRotaGraph(pos_.x, pos_.y, 1.0, angle, img, 1);

	angle += 0.15f;
}

//----------------------------------------------------------------------------------------------------