#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//コンストラクタ
GameManager::GameManager() {

}


//----------------------------------------------------------------------------------------------------
//初期化
void GameManager::Init() {

	if (!_init) { return; }

	STp = new TitleScene();
	SMp = new MenuScene();
	SPp = new PlayScene();

	STp->alive_flag = true;

	Sp.emplace_back(STp);
	Sp.emplace_back(SMp);
	Sp.emplace_back(SPp);

	_init = false;
}


//----------------------------------------------------------------------------------------------------
//背景
void GameManager::DrawBuckGround() {

	for (int y = -FIELD_H; y < FIELD_H; y += 16) {
		for (int x = -FIELD_W; x < FIELD_W; x += 16) {

			DrawGraph(x, y, img, false);
		}
	}
}


//----------------------------------------------------------------------------------------------------
//シーン遷移
void GameManager::ChangeScene() {

	if (STp->alive_flag && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD1)) {
		STp->alive_flag = false;
		SMp->alive_flag = true;

		return;
	}

	if (SMp->alive_flag && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD2)) {
		SMp->alive_flag = false;
		STp->alive_flag = true;

		return;
	}

	if (SMp->alive_flag && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD3)) {
		SMp->alive_flag = false;
		SPp->alive_flag = true;

		return;
	}

	if (SPp->alive_flag && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD4)) {
		SPp->alive_flag = false;
		SMp->alive_flag = true;

		return;
	}
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void GameManager::Update(float deltatime) {

	Init();

	for (auto pointer : Sp) {

		if (pointer->alive_flag) { pointer->Update(deltatime); }
	}

	ChangeScene();
}
void GameManager::Render(float deltatime) {

	for (auto pointer : Sp) {

		if (pointer->alive_flag) { pointer->Render(deltatime); }
	}

}
//----------------------------------------------------------------------------------------------------