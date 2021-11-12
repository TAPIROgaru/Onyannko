#include "Camera.h"
#include "GameManager.h"


extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Camera::Camera() {

}

//----------------------------------------------------------------------------------------------------

void Camera::update(float deltatime, t2k::Vector3 pos_) {

	if (pos.x < -GMp->FIELD_W + GMp->SCREEN_W / 2) {
		pos.x = -GMp->FIELD_W + GMp->SCREEN_W / 2;
	}
	else if (pos.x > GMp->FIELD_W - GMp->SCREEN_W / 2) {
		pos.x = GMp->FIELD_W - GMp->SCREEN_W / 2;
	}

	if (pos.y < -GMp->FIELD_H + GMp->SCREEN_H / 2) {
		pos.y = -GMp->FIELD_H + GMp->SCREEN_H / 2;
	}
	else if (pos.y > GMp->FIELD_H - GMp->SCREEN_H / 2) {
		pos.y = GMp->FIELD_H - GMp->SCREEN_H / 2;
	}

	pos += (pos_ - pos) * 0.1f;

	DrawFormatString(0, 50, -1, "camera x:%lf y:%lf", pos.x, pos.y);
}