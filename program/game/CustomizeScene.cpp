#include "CustomizeScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
CustomizeScene::CustomizeScene() {

	img = GMp->loadGraph("graphics/back.png");
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

void CustomizeScene::Update(float deltatime) {


}
void CustomizeScene::Render(float deltatime) {

	DrawGraph(0, 0, img, true);
}

//----------------------------------------------------------------------------------------------------