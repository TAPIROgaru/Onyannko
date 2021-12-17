#include "MenuScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
MenuScene::MenuScene() {

	img = GMp->loadGraph("graphics/back.png");
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void MenuScene::Update(float deltatime) {


}
void MenuScene::Render(float deltatime) {

	DrawGraph(0, 0, img, true);
}

//----------------------------------------------------------------------------------------------------