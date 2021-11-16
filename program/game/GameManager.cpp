#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//コンストラクタ
GameManager::GameManager() {

	img_aim = LoadGraph("graphics/AIM.png");
	img_mouse = LoadGraph("graphics/mouse.png");
}


//----------------------------------------------------------------------------------------------------
//初期化
void GameManager::Init() {

	if (!_init) { return; }

	STp = new TitleScene();
	SMp = new MenuScene();
	SPp = new PlayScene();
	SRp = new ResultScene();

	STp->_switch = true;

	Sp.emplace_back(STp);
	Sp.emplace_back(SMp);
	Sp.emplace_back(SPp);
	Sp.emplace_back(SRp);

	_init = false;
}


//----------------------------------------------------------------------------------------------------
//シーン遷移
void GameManager::ChangeScene() {

	if (STp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD1)) {
		STp->_switch = false;
		SMp->_switch = true;

		return;
	}

	if (SMp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD2)) {
		SMp->_switch = false;
		STp->_switch = true;

		return;
	}

	if (SMp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD3)) {
		SMp->_switch = false;
		SPp->_switch = true;
		SPp->_init = true;

		return;
	}

	if (SPp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_NUMPAD4)) {
		SPp->_switch = false;
		SRp->_switch = false;
		SMp->_switch = true;

		

		return;
	}
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void GameManager::Update(float deltatime) {

	Init();

	for (auto p : Sp) {

		if (p->_switch) { p->Update(deltatime); }
	}

	ChangeScene();
}
void GameManager::Render(float deltatime) {

	for (auto p : Sp) {

		if (p->_switch) { p->Render(deltatime); }
	}

	int x, y;
	GetMousePoint(&x, &y);

	if (SPp->_switch) {
		DrawRotaGraph(x, y, 0.05f, 0, img_aim, true);
	}
	else {
		DrawRotaGraph(x, y, 0.05f, 0, img_mouse, true);
	}
}
//----------------------------------------------------------------------------------------------------