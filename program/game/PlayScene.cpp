#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Square.h"
#include "ResultScene.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
PlayScene::PlayScene() {

	datas = GMp->datas;

	map = t2k::loadCsv("BackGround.csv");
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

	//Playerポインタ
	if (!Pp->alive_flag) {

		delete (Pp);
		Pp = nullptr;
	}

	//Enemyポインタ
	if (!Ep->alive_flag) {

		delete (Ep);
		Ep = nullptr;
	}
}


//----------------------------------------------------------------------------------------------------
//背景
void PlayScene::LoadBuckGround() {



	//float x = -GMp->FIELD_W - GMp->TILE_SIZE_W * 2;
	float x = -GMp->TILE_SIZE_W * 3;
	//float y = -GMp->FIELD_H - GMp->TILE_SIZE_H * 2;
	float y = -GMp->TILE_SIZE_H * 3;

	int _y = 0;

	for (auto i : map) {
		x = -GMp->TILE_SIZE_W * 3;

		std::vector<int> map_y;

		for (auto k : i) {

			int img = 0;
			int num = std::atoi(k.c_str());

			switch (num) {

			case FLOOR:
				img = GMp->loadGraph("graphics/kusa.png");

				map_y.emplace_back(2);

				break;

			case OUTSIDE_WALL:
			case INSIDE_WALL:
				img = GMp->loadGraph("graphics/shasen.png");

				break;

			case ROCK:
				img = GMp->loadGraph("graphics/isi.png");

				map_y.emplace_back(3);

				break;

			default:
				break;
			}

			Square* sp = new Square(
				t2k::Vector3(x, y, 0),
				img
			);

			Op.emplace_back(sp);
			Sp.emplace_back(sp);

			if (num == ROCK || num == INSIDE_WALL) {
				Sp_wall.emplace_back(sp);
			}

			x += GMp->TILE_SIZE_W;
		}
		y += GMp->TILE_SIZE_H;

		if (!map_y.empty()) {
			astar_map.emplace_back(map_y);
		}
	}
}


//----------------------------------------------------------------------------------------------------
//スタート
void PlayScene::Start(float deltatime) {

	if (!_switch || count >= 5) { return; }

	count += deltatime;

	if (count < 3) { return; }

	if (count < 5) { _start_flag = true; return; }
}


//----------------------------------------------------------------------------------------------------
//セーブ
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);
	fwrite(&Pp->ult->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillA->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillB->my_number, sizeof(int), 1, fp);

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

bool PlayScene::isHit_Wall(t2k::Vector3 pos, float r) {

	for (auto p : Sp_wall) {

		float x = p->pos.x + (p->size_w_ >> 1);
		float y = p->pos.y + (p->size_h_ >> 1);
		t2k::Vector3 box_pos = { x, y, 0 };

		t2k::Vector3 pos_ = t2k::getNearestRectPoint(
			box_pos,
			p->size_w_,
			p->size_h_,
			pos
		);

		if (isHit_DotAndCircle(pos_, pos, r)) { return true; }
	}

	return false;
}

void PlayScene::isHit_Wall(t2k::Vector3& pos, t2k::Vector3 prev_pos, float r) {

	//posに近い順にソート
	Sp_wall.sort([&](Square* l, Square* r) {
		float ld = (pos - l->pos).length();
		float rd = (pos - r->pos).length();
		return (ld < rd);
	});

	for (auto p : Sp_wall) {

		float x = p->pos.x + (p->size_w_ >> 1);
		float y = p->pos.y + (p->size_h_ >> 1);
		t2k::Vector3 box_pos = { x, y, 0 };

		t2k::Vector3 pos_ = t2k::getNearestRectPoint(
			box_pos,
			p->size_w_,
			p->size_h_,
			pos
		);

		if (isHit_DotAndCircle(pos_, pos, r)){

			int num = t2k::getRegionPointAndRect(prev_pos, t2k::Vector3(x, y, 0), p->size_w_, p->size_h_);

			isHit_ActionCorrectionPosition(pos, r, pos_, num);
		}
	}
}

inline bool PlayScene::isHit_DotAndCircle(t2k::Vector3 dot_pos, t2k::Vector3 cir_pos, float r) {

	float x = dot_pos.x - cir_pos.x;
	float y = dot_pos.y - cir_pos.y;

	if (x * x + y * y <= r * r) {

		return true;
	}

	return false;
}

inline void PlayScene::isHit_ActionCorrectionPosition(t2k::Vector3& pos, float r, t2k::Vector3 dot_pos, int num) {

	const int HIT_UP = 2;     //上に当たった
	const int HIT_DOWN = 0;   //下に当たった
	const int HIT_RIGHT = 3;  //右に当たった
	const int HIT_LEFT = 1;   //左に当たった

	//下に補正
	if (num == HIT_UP) {

		pos.y = (dot_pos.y + 1 + r);
	}
	//上に補正
	if (num == HIT_DOWN) {

		pos.y = (dot_pos.y - 1 - r);
	}
	//左に補正
	if (num == HIT_RIGHT) {

		pos.x = (dot_pos.x - 1 - r);
	}
	//右の補正
	if (num == HIT_LEFT) {

		pos.x = (dot_pos.x + 1 + r);
	}
}



//----------------------------------------------------------------------------------------------------
//Astar用のPlayerとEnemyの二次元座標作製

void PlayScene::MakeVector2(tpr::Vector2* p_pos, tpr::Vector2* e_pos) {

	*p_pos = tpr::Vector2{
		(int)Pp->pos.x / GMp->TILE_SIZE_W,
		(int)Pp->pos.y / GMp->TILE_SIZE_H
	};

	*e_pos = tpr::Vector2{
		(int)Ep->pos.x / GMp->TILE_SIZE_W,
		(int)Ep->pos.y / GMp->TILE_SIZE_H
	};
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

tpr::Vector2 PlayScene::FixPositionVector(tpr::Vector2 pos) {

	tpr::Vector2 pos_ = {
		(int)(pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1)),
		(int)(pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1))
	};

	return pos_;
}


//----------------------------------------------------------------------------------------------------
//初期化
void PlayScene::Init() {

	if (!_init) { return; }

	LoadBuckGround();

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

	Start(deltatime);

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

	cam.render();
}

//----------------------------------------------------------------------------------------------------