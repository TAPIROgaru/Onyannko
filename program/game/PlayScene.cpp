#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
PlayScene::PlayScene() {

	datas = t2k::loadCsv("Charactor_Status.csv");
}


//----------------------------------------------------------------------------------------------------
//消す
void PlayScene::Delete() {

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
//スタート
void PlayScene::Start(float deltatime) {

	if (!alive_flag) { return; }

	count += deltatime;

	if (count < 3) {

		DrawFormatString(0, 10, -1, "よーい　%f", count);
		return;
	}

	DrawString(0, 10, "スタート", -1);
	_start_flag = true;
}


//----------------------------------------------------------------------------------------------------
//セーブ
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//ゲームオーバー
void PlayScene::isOver() {

	//if(Pp->)
}


//----------------------------------------------------------------------------------------------------
//当たり判定
void PlayScene::isHit() {

	//当たり判定は個対多で行う
}


//----------------------------------------------------------------------------------------------------
//弾作成
void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, float a, bool t) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, a, t);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//カメラを考慮したマウス座標の取得
t2k::Vector3 PlayScene::GetMousePosition() {

	int x, y;
	GetMousePoint(&x, &y);

	t2k::Vector3 pos = { 0,0,0 };

	//カメラを考慮
	pos.x = x + cam.pos.x - (GameManager::SCREEN_W >> 1);
	pos.y = y + cam.pos.y - (GameManager::SCREEN_H >> 1);

	return pos;
}

//カメラを考慮した座標の取得
t2k::Vector3 PlayScene::FixPositionVector(t2k::Vector3 pos) {

	t2k::Vector3 pos_ = {
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1),
		0
	};

	return pos_;
}


//----------------------------------------------------------------------------------------------------
//初期化
void PlayScene::Init() {

	if (!_init) { return; }

	Pp = new Player();
	Op.emplace_back(Pp);

	Ep = new Enemy(1);
	Op.emplace_back(Ep);

	_init = false;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void PlayScene::Update(float deltatime) {

	Init();

	cam.pos += (Pp->pos - cam.pos) * 0.1f;
	Start(deltatime);

	for (auto pointer : Op) {

		if (pointer->alive_flag) { pointer->Update(deltatime); }
	}
}
void PlayScene::Render(float deltatime) {

	for (auto pointer : Op) {

		if (pointer->alive_flag) { pointer->Render(&cam); }
	}
}

//----------------------------------------------------------------------------------------------------