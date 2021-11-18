#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
PlayScene::PlayScene() {

	datas = GMp->datas;

	map = t2k::loadCsv("BackGround.csv");

	img_bullet = GMp->loadGraph("graphics/shuriken.png");
	img_back[0] = GMp->loadGraph("graphics/kusa.png");
	img_back[1] = GMp->loadGraph("graphics/shasen.png");
	img_back[2] = GMp->loadGraph("graphics/isi.png");
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

	//Squareポインタ型のリスト
	std::list<Square*>::iterator Spit = Sp.begin();
	while (Spit != Sp.end()) {
		if (!(*Spit)->alive_flag) {

			Spit = Sp.erase(Spit);
			continue;
		}
		Spit++;
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
//背景
void PlayScene::DrawBuckGround() {

	

	float x = -GMp->FIELD_W - 16 * 3;
	float y = -GMp->FIELD_H - 16 * 2;

	for (auto i : map) {
		x = -GMp->FIELD_W - 16 * 3;
		for (auto k : i) {

			Square* sp = new Square(
				t2k::Vector3(x, y, 0), 
				img_back[std::atoi(k.c_str())], 
				std::atoi(k.c_str()));

			Op.emplace_back(sp);
			Sp.emplace_back(sp);

			if (std::atoi(k.c_str()) != FLOOR) {
				Sp_wall.emplace_back(sp);
			}

			x += 16;
		}
		y += 16;
	}
}


//----------------------------------------------------------------------------------------------------
//スタート
void PlayScene::Start(float deltatime) {

	if (!_switch || count >= 5) { return; }

	count += deltatime;

	if (count < 3) {

		DrawFormatString(0, 0, -1, "よーい　%f", count);
		return;
	}

	if (count < 5) {
		DrawString(0, 0, "スタート", -1);
		_start_flag = true;
		return;
	}
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

	if (Pp->_hp == 0 || Ep->sta.HP == 0) {

		GMp->SRp->_switch = true;
	}
}


//----------------------------------------------------------------------------------------------------
//当たり判定
//弾
void PlayScene::isHit_bullet() {

	for (auto p : Bp) {
		if (p->_team) {
			if (CircleHit(Ep->pos.x, Ep->pos.y, Ep->r, p->pos.x, p->pos.y, p->r)) {
				Ep->sta.HP--;
				p->alive_flag = false;
			}
		}
		else if (!p->_team) {
			if (CircleHit(Pp->pos.x, Pp->pos.y, Pp->r, p->pos.x, p->pos.y, p->r)) {
				Pp->_hp--;
				p->alive_flag = false;
			}
		}
	}
}
//壁
void PlayScene::isHit_wall() {

	Sp_wall.sort([&](Square* l, Square* r) {
		float ld = (Pp->pos - l->pos).length();
		float rd = (Pp->pos - r->pos).length();
		return (ld < rd);
	});

	for (auto p : Sp_wall) {

		float x = p->pos.x + (p->size_w_ >> 1);
		float y = p->pos.y + (p->size_h_ >> 1);

		t2k::Vector3 pos_ = t2k::getNearestRectPoint(
			t2k::Vector3(x, y, 0),
			p->size_w_,
			p->size_w_,
			Pp->pos
			);
	}
}

//----------------------------------------------------------------------------------------------------
//弾作成
void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, bool t) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, t);
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

	DrawBuckGround();

	Pp = new Player();
	Op.emplace_back(Pp);

	Ep = new Enemy(1);
	Op.emplace_back(Ep);

	count = 0;
	_start_flag = false;

	_init = false;
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し
void PlayScene::Update(float deltatime) {

	Init();

	for (auto p : Op) {

		if (p->alive_flag) { p->Update(deltatime); }
	}

	cam.update(deltatime, Pp->pos);

	isHit_bullet();
	Delete();

	isOver();
}
void PlayScene::Render(float deltatime) {

	for (auto p : Op) {

		if (p->alive_flag) { p->Render(&cam); }
	}

	Start(deltatime);

	cam.render();
}

//----------------------------------------------------------------------------------------------------