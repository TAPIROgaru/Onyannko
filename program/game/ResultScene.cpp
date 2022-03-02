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
	win_img = GMp->loadGraph("graphics/win.png");
	lose_img = GMp->loadGraph("graphics/lose.png");
	player_img = GMp->loadGraph("graphics/playr_menu.png");


	bgm = GMp->loadSoundMem("sound/bgm_other.mp3");
	ChangeVolumeSoundMem(255 * 0.2, bgm);
	
	sound[0] = GMp->loadSoundMem("sound/result1.mp3");
	ChangeVolumeSoundMem(255 * 0.5, sound[0]);
	sound[1] = GMp->loadSoundMem("sound/result_win.mp3");
	ChangeVolumeSoundMem(255 * 0.5, sound[1]);
	sound[2] = GMp->loadSoundMem("sound/result_lose.mp3");
	ChangeVolumeSoundMem(255 * 0.5, sound[2]);
}



void ResultScene::ChangeMenuScene() {

	if (CheckHitKeyAll(DX_CHECKINPUT_KEY) != 0) {
		_switch = false;
		GMp->SMp->_switch = true;
		GMp->SMp->_init = true;
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
		PlaySoundMem(sound[play_num], DX_PLAYTYPE_BACK);
		_init = false;
	}

	if (_effect) {
		if (count > 2.0) { StopSoundMem(sound[0]); }
		if (CheckSoundMem(sound[play_num]) == 1) { return; }
		if (_win_or_lose) { play_num++; _effect = false; }
		if (!_win_or_lose) { play_num += 2; _effect = false; }

		PlaySoundMem(sound[play_num], DX_PLAYTYPE_BACK);
	}

	ChangeMenuScene();
}
void ResultScene::Render(float deltatime) {


	DrawRotaGraph(GMp->SCREEN_W / 2, GMp->SCREEN_H / 2, 1.0, 0, img_back_black, true);
	if (_effect) { return; }
	DrawRotaGraph(GMp->SCREEN_W / 2, 500, 0.5, 0, push_img, true);
	DrawRotaGraph(GMp->SCREEN_W / 2 - 250, GMp->SCREEN_H / 2, 0.5, 0, player_img, true);
	if (_win_or_lose) {
		DrawRotaGraph(GMp->SCREEN_W / 2 + 250, GMp->SCREEN_H / 2, 1.0, 0, win_img, true);
	}
	else if (!_win_or_lose) {
		DrawRotaGraph(GMp->SCREEN_W / 2 + 200, GMp->SCREEN_H / 2, 1.0, 0, lose_img, true);
	}
}

//----------------------------------------------------------------------------------------------------