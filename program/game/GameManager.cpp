#include "GameManager.h"
#include "Scene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "Player.h"


//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
GameManager::GameManager() {

	datas = t2k::loadCsv("Charactor_Status.csv");

	img_aim = loadGraph("graphics/AIM.png");
	img_mouse = loadGraph("graphics/mouse.png");
}


//----------------------------------------------------------------------------------------------------
//������
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
//�V�[���J��
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
//�摜�Ăяo��

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
//�Z�[�u
void GameManager::SavePlayer(Player* p) {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(p->name, sizeof(p->name), 1, fp);
	fwrite(&p->sta.HP, sizeof(int), 1, fp);
	fwrite(&p->default_speed, sizeof(int), 1, fp);
	fwrite(&p->sta.attack, sizeof(int), 1, fp);
	fwrite(&p->sta.defense, sizeof(int), 1, fp);
	fwrite(&p->sta.attack_speed, sizeof(int), 1, fp);
	fwrite(&p->ult->my_number, sizeof(int), 1, fp);
	fwrite(&p->skillA->my_number, sizeof(int), 1, fp);
	fwrite(&p->skillB->my_number, sizeof(int), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��

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