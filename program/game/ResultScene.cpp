#include "ResultScene.h"
#include "GameManager.h"
#include "MenuScene.h"
#include "PlayScene.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
ResultScene::ResultScene() {

	img_back_black = GMp->loadGraph("graphics/BuckBlack.png");
	push_img = GMp->loadGraph("graphics/pushanybotton.png");
}



void ResultScene::ChangeMenuScene() {

	if (CheckHitKeyAll(DX_CHECKINPUT_KEY) != 0) {
		_switch = false;
		GMp->SMp->_switch = true;
		GMp->SPp->_switch = false;
		GMp->SPp->_init= true;
	}
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void ResultScene::Update(float deltatime) {

	ChangeMenuScene();
}
void ResultScene::Render(float deltatime) {


	DrawRotaGraph(GMp->SCREEN_W / 2, GMp->SCREEN_H / 2, 1.0, 0, img_back_black, true);
	DrawRotaGraph(GMp->SCREEN_W / 2, 500, 0.5, 0, push_img, true);

}

//----------------------------------------------------------------------------------------------------