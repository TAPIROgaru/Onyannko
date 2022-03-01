#include "DxLib.h"

#include "TitleScene.h"
#include "GameManager.h"
#include "MenuScene.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
TitleScene::TitleScene() {

	img = GMp->loadGraph("graphics/title.png");
	name_img = GMp->loadGraph("graphics/title_name.png");
	control_img = GMp->loadGraph("graphics/control.png");
	push_img = GMp->loadGraph("graphics/pushanybotton.png");
}


//----------------------------------------------------------------------------------------------------
//
void TitleScene::ChangeMenuScene() {

	if (CheckHitKeyAll(DX_CHECKINPUT_ALL) != 0) {
		_switch = false;
		GMp->SMp->_switch = true;
	}
}

//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void TitleScene::Update(float deltatime) {

	ChangeMenuScene();
}
void TitleScene::Render(float deltatime) {

	DrawRotaGraph(GMp->SCREEN_W / 2, GMp->SCREEN_H / 2, 1.0, 0, img, true);
	DrawRotaGraph(GMp->SCREEN_W / 2, 200, 1.0, 0, name_img, true);
	DrawRotaGraph(GMp->SCREEN_W - 90, 60, 0.5, 0, control_img, true);
	DrawRotaGraph(GMp->SCREEN_W / 2, 400, 0.5, 0, push_img, true);

}

//----------------------------------------------------------------------------------------------------