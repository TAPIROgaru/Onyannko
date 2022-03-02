#include "MenuScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
MenuScene::MenuScene() {

	img = GMp->loadGraph("graphics/back.png");
	bgm = GMp->loadSoundMem("sound/bgm_other.mp3");
	ChangeVolumeSoundMem(255 * 0.2, bgm);
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void MenuScene::Update(float deltatime) {

	if (_init) {
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
		_init = false;
	}

}
void MenuScene::Render(float deltatime) {

	DrawGraph(0, 0, img, true);
}

//----------------------------------------------------------------------------------------------------