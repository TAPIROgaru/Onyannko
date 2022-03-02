#include "ResultScene.h"
#include "GameManager.h"
#include "MenuScene.h"
#include "PlayScene.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
ResultScene::ResultScene() {

	img_back_black = GMp->loadGraph("graphics/BuckBlack.png");
	push_img = GMp->loadGraph("graphics/pushanybotton.png");
	bgm = GMp->loadSoundMem("sound/bgm_other.mp3");
	ChangeVolumeSoundMem(255 * 0.2, bgm);
}



void ResultScene::ChangeMenuScene() {

	if (CheckHitKeyAll(DX_CHECKINPUT_KEY) != 0) {
		_switch = false;
		GMp->SMp->_switch = true;
		GMp->SPp->_switch = false;
		GMp->SPp->_init= true;

		GMp->SPp->Op.clear();
		GMp->SPp->Bp.clear();
		GMp->SPp->Sp.clear();
		GMp->SPp->Sp_wall.clear();

		if (GMp->SPp->Pp != nullptr) {
			delete GMp->SPp->Pp;
			GMp->SPp->Pp = nullptr;
		}
		if (GMp->SPp->Ep != nullptr) {
			delete GMp->SPp->Ep;
			GMp->SPp->Ep = nullptr;
		}

		PlaySoundMem(GMp->scene_sou, DX_PLAYTYPE_BACK);
	}
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void ResultScene::Update(float deltatime) {

	if (_init) {
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		_init = false;
	}

	ChangeMenuScene();
}
void ResultScene::Render(float deltatime) {


	DrawRotaGraph(GMp->SCREEN_W / 2, GMp->SCREEN_H / 2, 1.0, 0, img_back_black, true);
	DrawRotaGraph(GMp->SCREEN_W / 2, 500, 0.5, 0, push_img, true);

}

//----------------------------------------------------------------------------------------------------