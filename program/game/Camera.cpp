#include "Camera.h"
#include "GameManager.h"


extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Camera::Camera() {

	pos = { GameManager::SCREEN_W >> 1 ,  GameManager::SCREEN_H >> 1, 0 };
}

//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void Camera::update(float deltatime, t2k::Vector3 pos_) {

	if (pos.x < (GMp->SCREEN_W >> 1) - GMp->TILE_SIZE_W) {
		pos.x = (GMp->SCREEN_W >> 1) - GMp->TILE_SIZE_W;
	}
	else if (pos.x > GMp->FIELD_W * 2 - (GMp->SCREEN_W >> 1) - GMp->TILE_SIZE_W) {
		pos.x = GMp->FIELD_W * 2 - (GMp->SCREEN_W >> 1) - GMp->TILE_SIZE_W;
	}

	if (pos.y < (GMp->SCREEN_H >> 1) - GMp->TILE_SIZE_H) {
		pos.y = (GMp->SCREEN_H >> 1) - GMp->TILE_SIZE_H;
	}
	else if (pos.y > GMp->FIELD_H * 2 - (GMp->SCREEN_H >> 1) - GMp->TILE_SIZE_H) {
		pos.y = GMp->FIELD_H * 2 - (GMp->SCREEN_H >> 1) - GMp->TILE_SIZE_H;
	}

	pos += (pos_ - pos) * 0.1f;
}
void Camera::render() {}
//----------------------------------------------------------------------------------------------------