#include "DxLib.h"

#include "TitleScene.h"
#include "GameManager.h"
#include "MenuScene.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
TitleScene::TitleScene() {

	img = GMp->loadGraph("graphics/title.png");
	name_img = GMp->loadGraph("graphics/title_name.png");
	control_img = GMp->loadGraph("graphics/control.png");
	push_img = GMp->loadGraph("graphics/pushanybotton.png");
	bgm = GMp->loadSoundMem("sound/bgm_title.mp3");
	ChangeVolumeSoundMem((int)(255 * 0.2), bgm);
}


//----------------------------------------------------------------------------------------------------
//
void TitleScene::ChangeMenuScene() {

	if (CheckHitKeyAll(DX_CHECKINPUT_ALL) != 0) {
		_switch = false;
		GMp->SMp->_switch = true;

		PlaySoundMem(GMp->scene_sou, DX_PLAYTYPE_BACK);
		if (CheckSoundMem(bgm) == 1) {
			StopSoundMem(bgm);
		}
	}
}

//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void TitleScene::Update(float deltatime) {

	if (_init) {

		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, true);
		_init = false;
	}

	ChangeMenuScene();
}
void TitleScene::Render(float deltatime) {

	DrawRotaGraph(GMp->SCREEN_W / 2, GMp->SCREEN_H / 2, 1.0, 0, img, true);
	DrawRotaGraph(GMp->SCREEN_W / 2, 200, 1.0, 0, name_img, true);
	DrawRotaGraph(GMp->SCREEN_W - 90, 60, 0.5, 0, control_img, true);
	DrawRotaGraph(GMp->SCREEN_W / 2, 400, 0.5, 0, push_img, true);

}

//----------------------------------------------------------------------------------------------------