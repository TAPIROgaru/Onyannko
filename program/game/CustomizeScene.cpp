#include "CustomizeScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
CustomizeScene::CustomizeScene() {

	img = GMp->loadGraph("graphics/back.png");
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void CustomizeScene::Update(float deltatime) {


}
void CustomizeScene::Render(float deltatime) {

	DrawGraph(0, 0, img, true);
}

//----------------------------------------------------------------------------------------------------