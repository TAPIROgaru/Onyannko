#include "Camera.h"
#include "GameManager.h"


extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//コンストラクタ
Camera::Camera() {

	pos = { GameManager::SCREEN_W ,  GameManager::SCREEN_H, 0 };
}

//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void Camera::update(float deltatime, t2k::Vector3 pos_) {

	//if (pos.x < -GMp->FIELD_W + GMp->SCREEN_W / 2) {
	//	pos.x = -GMp->FIELD_W + GMp->SCREEN_W / 2;
	//}
	//else if (pos.x > GMp->FIELD_W - GMp->SCREEN_W / 2) {
	//	pos.x = GMp->FIELD_W - GMp->SCREEN_W / 2;
	//}

	//if (pos.y < -GMp->FIELD_H + GMp->SCREEN_H / 2) {
	//	pos.y = -GMp->FIELD_H + GMp->SCREEN_H / 2;
	//}
	//else if (pos.y > GMp->FIELD_H - GMp->SCREEN_H / 2) {
	//	pos.y = GMp->FIELD_H - GMp->SCREEN_H / 2;
	//}

	pos += (pos_ - pos) * 0.1f;
}
void Camera::render() {}
//----------------------------------------------------------------------------------------------------