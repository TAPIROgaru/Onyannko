#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//コンストラクタ
GameManager::GameManager() {

	img = LoadGraph("graphics/sample.jpg");
}

//初期化
void GameManager::Init() {

	Pp = new Player();
	Op.emplace_back(Pp);

}

//タイトル
bool GameManager::Title(const float deltatime) {

	DrawFormatString(100, 100, -1, "タイトル");

	if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_RETURN)) {
		seq.change(&GameManager::Play);
	}

	return true;
}

//プレイ画面
bool GameManager::Play(const float deltatime) {

	if (seq.isStart()) {
		Init();
	}

	cam.pos += (Pp->pos - cam.pos) * 0.1f;

	return true;
}

//----------------------------------------------------------------------------------------------------
//消す
void GameManager::Delete() {

	//Bulletポインタ型のリスト
	std::list<Bullet*>::iterator Bpit = Bp.begin();
	while (Bpit != Bp.end()) {
		if (!(*Bpit)->alive_flag) {

			Bpit = Bp.erase(Bpit);
			continue;
		}
		Bpit++;
	}

	//Objectポインタ型のリスト
	std::list<Object*>::iterator Opit = Op.begin();
	while (Opit != Op.end()) {
		if (!(*Opit)->alive_flag) {

			delete (*Opit);
			Opit = Op.erase(Opit);
			continue;
		}
		Opit++;
	}
}


//----------------------------------------------------------------------------------------------------
//弾作成
void GameManager::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, float a) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, a);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//セーブ
void GameManager::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//カメラを考慮したマウス座標の取得
t2k::Vector3 GameManager::GetMousePosition() {

	int x, y;
	GetMousePoint(&x, &y);

	t2k::Vector3 pos = { 0,0,0 };

	//カメラを考慮
	pos.x = x + cam.pos.x - (GameManager::SCREEN_W >> 1);
	pos.y = y + cam.pos.y - (GameManager::SCREEN_H >> 1);

	return pos;
}

//カメラを考慮した座標の取得
t2k::Vector3 GameManager::FixPositionVector(t2k::Vector3 pos) {

	t2k::Vector3 pos_ = {
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1),
		0
	};
	
	return pos_;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void GameManager::Update(float deltatime) {

	for (auto pointer : Op) {

		pointer->Update(deltatime);
	}

	seq.update(deltatime);

	Delete();
}
void GameManager::Render(float deltatime) {

	t2k::Vector3 pos_1 = FixPositionVector(img_pos1);
	t2k::Vector3 pos_2 = FixPositionVector(img_pos2);

	DrawExtendGraph(pos_1.x, pos_1.y, pos_2.x, pos_2.y, img, false);
	cam.update(deltatime);

	for (auto pointer : Op) {

		pointer->Render(&cam);
	}

}
//----------------------------------------------------------------------------------------------------