#include "MenuScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
MenuScene::MenuScene() {

	img = GMp->loadGraph("graphics/back.png");
	bgm = GMp->loadSoundMem("sound/bgm_other.mp3");
	ChangeVolumeSoundMem((int)(255 * 0.2), bgm);
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

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