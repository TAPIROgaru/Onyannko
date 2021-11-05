#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//ÉRÉìÉXÉgÉâÉNÉ^
GameManager::GameManager() {

	img = LoadGraph("graphics/sample.jpg");

	STp = new TitleScene();
	SMp = new MenuScene();
	SPp = new PlayScene();

	STp->alive_flag = true;

	Sp.emplace_back(STp);
	Sp.emplace_back(SMp);
	Sp.emplace_back(SPp);
}


//----------------------------------------------------------------------------------------------------
//îwåi
void GameManager::DrawBuckGround() {

	for (int y = -FIELD_H; y < FIELD_H; y += 16) {
		for (int x = -FIELD_W; x < FIELD_W; x += 16) {

			DrawGraph(x, y, img, false);
		}
	}
}


//----------------------------------------------------------------------------------------------------
//îwåi
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
//ñàÉtÉåÅ[ÉÄåƒÇ—èoÇµ

void GameManager::Update(float deltatime) {

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