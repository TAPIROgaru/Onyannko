#include "MenuScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
MenuScene::MenuScene() {

	img = GMp->loadGraph("graphics/back.png");
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void MenuScene::Update(float deltatime) {


}
void MenuScene::Render(float deltatime) {

	DrawGraph(0, 0, img, true);
}

//----------------------------------------------------------------------------------------------------