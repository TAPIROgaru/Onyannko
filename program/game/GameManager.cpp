#include "GameManager.h"
#include "Scene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "ResultScene.h"
#include "TitleScene.h"


//----------------------------------------------------------------------------------------------------
//コンストラクタ
GameManager::GameManager() {

	datas = t2k::loadCsv("Charactor_Status.csv");

	img_aim = loadGraph("graphics/AIM.png");
	img_mouse = loadGraph("graphics/mouse.png");
	scene_sou = loadSoundMem("sound/scene.mp3");
	ChangeVolumeSoundMem((int)(255 * 0.5), scene_sou);
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

	//if (SMp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_2)) {
	//	SMp->_switch = false;
	//	STp->_switch = true;

	//	PlaySoundMem(scene_sou, DX_PLAYTYPE_BACK);

	//	return;
	//}

	if (SMp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_3)) {
		SMp->_switch = false;
		SPp->_switch = true;
		SPp->_init = true;

		PlaySoundMem(scene_sou, DX_PLAYTYPE_BACK);

		if (CheckSoundMem(SMp->bgm) == 1) {
			StopSoundMem(SMp->bgm);
		}

		return;
	}

	if (SPp->_switch && t2k::Input::isKeyDown(t2k::Input::KEYBORD_4)) {
		SPp->_switch = false;
		SRp->_switch = false;
		SMp->_switch = true;

		PlaySoundMem(scene_sou, DX_PLAYTYPE_BACK);

		return;
	}
}


//----------------------------------------------------------------------------------------------------
//画像呼び出し

int GameManager::loadGraph(std::string str) {

	auto it =image.find(str);

	if (it != image.end()) {
		return it->second;
	}

	int img = LoadGraph(str.c_str());
	image.insert(std::make_pair(str, img));

	return img;
}

std::vector<int> GameManager::loadDivGraph(std::vector<std::string> str, int img_value) {

	std::vector<int> img;

	for (int i = 0; i < img_value; i++) {
		img.emplace_back(loadGraph(str[i]));
	}

	return img;
}


//----------------------------------------------------------------------------------------------------
//音源ファイル

int GameManager::loadSoundMem(std::string str) {

	auto it = sound.find(str);

	if (it != sound.end()) {
		return it->second;
	}

	int sou = LoadSoundMem(str.c_str());
	sound.insert(std::make_pair(str, sou));

	return sou;

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
	DrawRotaGraph(x, y, 0.05f, 0, img_aim, true);
}
//----------------------------------------------------------------------------------------------------