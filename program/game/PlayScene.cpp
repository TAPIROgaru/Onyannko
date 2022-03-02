#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"
#include "Square.h"
#include "ResultScene.h"
#include "TPRlib/tpr_library.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
PlayScene::PlayScene() {

	datas = GMp->datas;

	map = t2k::loadCsv("BackGround.csv");
	bgm = GMp->loadSoundMem("sound/bgm_play.mp3");
	ChangeVolumeSoundMem(255 * 0.2, bgm);
	count_sou[0]= GMp->loadSoundMem("sound/start_count.mp3");
	count_sou[1]= GMp->loadSoundMem("sound/start.mp3");

	count_img[0] = GMp->loadGraph("graphics/count3.png");
	count_img[1] = GMp->loadGraph("graphics/count2.png");
	count_img[2] = GMp->loadGraph("graphics/count1.png");
	count_img[3] = GMp->loadGraph("graphics/start.png");

	//=============================================================================
	//デバッグ用

	if (!GameManager::DEBUG_MODE) { return; }

	map = t2k::loadCsv("BackGroundDebug.csv");

	//=============================================================================
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
void PlayScene::ForcedDelete() {

	std::vector<Scroll*>::iterator spit = scroll_p.begin();
	while (spit != scroll_p.end()) {
		delete (*spit);
		spit = scroll_p.erase(spit);
		continue;
		spit++;
	}
}


//----------------------------------------------------------------------------------------------------
//背景
void PlayScene::LoadBuckGround() {

	float x = -GMp->TILE_SIZE_W * 3;
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

	if (CheckSoundMem(count_sou[0]) == 0) {
		PlaySoundMem(count_sou[0], DX_PLAYTYPE_BACK);
	}

	if (count < 1) { return; }

	draw_num = 0;

	if (count < 2) { return; }

	draw_num = 1;

	if (count < 3) { return; }

	draw_num = 2;

	if (count < 4) { return; }

	draw_num = 3;

	if (CheckSoundMem(count_sou[0]) == 1) {
		StopSoundMem(count_sou[0]);
	}

	if (CheckSoundMem(count_sou[1]) == 0) {
		PlaySoundMem(count_sou[1], DX_PLAYTYPE_BACK);
	}

	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	_start_flag = true;
}


//----------------------------------------------------------------------------------------------------
//セーブ
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->origin_sta.HP, sizeof(int), 1, fp);
	fwrite(&Pp->origin_sta.move_speed, sizeof(int), 1, fp);
	fwrite(&Pp->origin_sta.attack, sizeof(int), 1, fp);
	fwrite(&Pp->origin_sta.defense, sizeof(int), 1, fp);
	fwrite(&Pp->origin_sta.attack_speed, sizeof(int), 1, fp);
	fwrite(&Pp->ult->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillA->my_number, sizeof(int), 1, fp);
	fwrite(&Pp->skillB->my_number, sizeof(int), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//ゲームオーバー
void PlayScene::isOver() {

	if (Pp->sta.hp_ == 0 || Ep->sta.hp_ == 0) {

		GMp->SRp->_switch = true;
		StopSoundMem(bgm);

		if (Ep->sta.hp_ == 0)GMp->SRp->_win_or_lose = true;
		else if (Pp->sta.hp_ == 0)GMp->SRp->_win_or_lose = false;
	}
}


//----------------------------------------------------------------------------------------------------
//当たり判定

void PlayScene::isHit_bullet() {

	for (auto p : Bp) {
		if (p->_team) {

			//当たり判定
			if (tpr::isHit_CircleAndCircle(
				tpr::Vector2(Ep->pos.x, Ep->pos.y),Ep->r,
				tpr::Vector2(p->pos.x, p->pos.y), p->r)) {

				if (!Ep->_invincible) {
					//ダメ計算
					int damage = Pp->sta.attack - Ep->sta.defense;

					//ダメ付与
					if (damage <= 0) { Ep->sta.hp_--; }
					else { Ep->sta.hp_ -= damage; }

					p->alive_flag = false;
				}
			}
		}
		else if (!p->_team) {
			if (tpr::isHit_CircleAndCircle(
				tpr::Vector2(Pp->pos.x, Pp->pos.y), Pp->r,
				tpr::Vector2(p->pos.x, p->pos.y), p->r)) {


				if (!Pp->_invincible) {
					//ダメ計算
					int damage = Ep->sta.attack - Pp->sta.defense;

					//ダメ付与
					if (damage <= 0) { Pp->sta.hp_--; }
					else { Pp->sta.hp_ -= damage; }

					p->alive_flag = false;
				}
			}
		}
	}
}

bool PlayScene::isHit_Wall(t2k::Vector3 pos, float r) {

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

		if (isHit_DotAndCircle(pos_, pos, r)) { return true; }
	}

	return false;
}

bool PlayScene::isHit_Wall(t2k::Vector3 pos,  t2k::Vector3 prev_pos, float r, int *num) {

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

		if (isHit_DotAndCircle(pos_, pos, r)) { 
			
			*num = t2k::getRegionPointAndRect(prev_pos, t2k::Vector3(x, y, 0),
				p->size_w_, p->size_h_);

			isHit_ActionCorrectionPosition(pos, r, pos_, *num);

			return true;
		}
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

			break;
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

bool PlayScene::isHit_RayAndWall() {

	tpr::Vector2 e_pos = FixPositionVector(tpr::Vector2(Ep->pos.x, Ep->pos.y));
	tpr::Vector2 p_pos = FixPositionVector(tpr::Vector2(Pp->pos.x, Pp->pos.y));

	//PlayerとEnemyをつなぐ矩形
	tpr::Quadrilateral ray_quad(e_pos, p_pos, GMp->BULLET_RADIUS * 3);

	auto p = Sp_wall.begin();
	while (p != Sp_wall.end()) {

		//Squareの座標データを四辺形にする

		t2k::Vector3 pos = FixPositionVector((*p)->pos);
		tpr::Vector2 pos_(pos.x + (GMp->TILE_SIZE_W >> 1), pos.y + (GMp->TILE_SIZE_H >> 1));
		tpr::Quadrilateral quad(pos_, (*p)->size_w_, (*p)->size_h_);

		if (tpr::isHit_RectangleAndRectangle(ray_quad, quad)) { return true; }

		p++;
	}

	return false;
}


//----------------------------------------------------------------------------------------------------
//Astar用のPlayerとEnemyの二次元座標作製

void PlayScene::MakeVector2(tpr::Vector2_int* p_pos, tpr::Vector2_int* e_pos) {

	*p_pos = tpr::Vector2_int{
		(int)Pp->pos.x / GMp->TILE_SIZE_W,
		(int)Pp->pos.y / GMp->TILE_SIZE_H
	};

	*e_pos = tpr::Vector2_int{
		(int)Ep->pos.x / GMp->TILE_SIZE_W,
		(int)Ep->pos.y / GMp->TILE_SIZE_H
	};
}


//----------------------------------------------------------------------------------------------------
// Enemyを始点、Playerを終点としたベクトルの単位ベクトルを得る

tpr::Vector2 PlayScene::Normalize() {

	tpr::Vector2 v = tpr::Vector2(Pp->pos.x - Ep->pos.x, Pp->pos.y - Ep->pos.y);

	float magnitude = sqrtf(v.x * v.x + v.y * v.y);

	tpr::Vector2 norm(v.x / magnitude, v.y / magnitude);

	return norm;
}

//----------------------------------------------------------------------------------------------------
//弾作成

void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, bool t) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, t);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}
Bullet* PlayScene::MakeBullet(tpr::Vector2 pos, tpr::Vector2 dire, int img, bool _team, float speed, float scope, int r) {

	Bullet* bp = new Bullet(pos, dire, img, _team, speed, scope, r);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);

	return bp;
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
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1)
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

	Ep = new Enemy(GMp->ENEMY_TAG);
	Op.emplace_back(Ep);

	count = 0;
	_start_flag = false;

	_init = false; 
	
	draw_num = -1;


	//=============================================================================
	//デバッグ用

	if (!GameManager::DEBUG_MODE) { return; }

	ForcedDelete();

	int m_x, m_y;
	GetMousePoint(&m_x, &m_y);

	for (int i = 0; i < 9; i++) {

		Scroll* s_p = nullptr;
		s_p = new Scroll(i, 40 * i, { (float)m_x, (float)m_y });
		scroll_p.emplace_back(s_p);
	}

	//=============================================================================
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

	//=============================================================================
	//デバッグ用

	if (!GameManager::DEBUG_MODE) { return; }

	int m_x, m_y;
	GetMousePoint(&m_x, &m_y);

	for (auto p : scroll_p) {

		p->Update(deltatime, { (float)m_x, (float)m_y });
	}

	char Buf[256];

	GetHitKeyStateAll(Buf);

	tpr::Vector2 pos_p = FixPositionVector({ Pp->pos.x,Pp->pos.y });
	tpr::Vector2 dire = tpr::Vector2::Normalize(pos_p, { (float)m_x,(float)m_y });

	if (Buf[KEY_INPUT_NUMPAD1] == 1) { scroll_p[0]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD2] == 1) { scroll_p[1]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD3] == 1) { scroll_p[2]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD4] == 1) { scroll_p[3]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD5] == 1) { scroll_p[4]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD6] == 1) { scroll_p[5]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD7] == 1) { scroll_p[6]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD8] == 1) { scroll_p[7]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }
	if (Buf[KEY_INPUT_NUMPAD9] == 1) { scroll_p[8]->Activate({ Pp->pos.x,Pp->pos.y }, dire.x, dire.y, Pp); }

	if (Buf[KEY_INPUT_O] == 1) { GMp->ENEMY_MODE = true; }
	if (Buf[KEY_INPUT_P] == 1) { GMp->ENEMY_MODE = false; }

	//=============================================================================
}
void PlayScene::Render(float deltatime) {

	for (auto p : Op) {

		if (p->alive_flag) { p->Render(&cam); }
	}

	cam.render();

	if (draw_num != -1) {
		DrawRotaGraph(GMp->SCREEN_W / 2, GMp->SCREEN_H / 2,
			2.0, 0, count_img[draw_num], true);

		if (draw_num == 3) {
			count += deltatime;
		}
		if (count > 5) { draw_num = -1; }
	}

	//=============================================================================
	//デバッグ用

	if (!GameManager::DEBUG_MODE) { return; }

	if (Pp == nullptr)return;

	tpr::Vector2 e_pos = FixPositionVector(tpr::Vector2(Ep->pos.x, Ep->pos.y));
	tpr::Vector2 p_pos = FixPositionVector(tpr::Vector2(Pp->pos.x, Pp->pos.y));

	//PlayerとEnemyをつなぐ矩形
	tpr::Quadrilateral ray_quad(e_pos, p_pos, GMp->BULLET_RADIUS * 3);

	ray_quad.DrawBox(-1);

	for (auto p : scroll_p) {

		p->RenderDebug(&cam);
	}

	//=============================================================================
}

//----------------------------------------------------------------------------------------------------