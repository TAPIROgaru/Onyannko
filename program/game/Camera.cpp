#include "Camera.h"
#include "GameManager.h"


extern GameManager* GMp;


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
Camera::Camera() {

}

//----------------------------------------------------------------------------------------------------

void Camera::update(float deltatime) {

	if (pos.x) {

	}
	DrawFormatString(0, 0, -1, "x:%lf y:%lf", pos.x, pos.y);
}