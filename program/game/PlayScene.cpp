#include "PlayScene.h"
#include "Camera.h"
#include "GameManager.h"
#include "Player.h"


extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//�R���X�g���N�^
PlayScene::PlayScene() {

	datas = t2k::loadCsv("Charactor_Status.csv");
	map = t2k::loadCsv("BackGround.csv");
	img_bullet = LoadGraph("graphics/shuriken.png");
	img_back[0] = LoadGraph("graphics/kusa.png");
	img_back[1] = LoadGraph("graphics/inviolability.png");
}


//----------------------------------------------------------------------------------------------------
//����
void PlayScene::Delete() {

	//Bullet�|�C���^�^�̃��X�g
	std::list<Bullet*>::iterator Bpit = Bp.begin();
	while (Bpit != Bp.end()) {
		if (!(*Bpit)->alive_flag) {

			Bpit = Bp.erase(Bpit);
			continue;
		}
		Bpit++;
	}

	//Object�|�C���^�^�̃��X�g
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
//�w�i
void PlayScene::DrawBuckGround() {

	t2k::Vector3 pos = { -GMp->FIELD_W - 16 * 3 ,-GMp->FIELD_H - 16 * 2, 0 };

	t2k::Vector3 pos_ = FixPositionVector(pos);

	float x = pos_.x;
	float y = pos_.y;

	for (auto i : map) {
		x = pos_.x;
		for (auto j : i) {

			DrawRotaGraph(x, y, 1.0, 0, img_back[std::atoi(j.c_str())], 1);
			x += 16;
		}
		y += 16;
	}
}


//----------------------------------------------------------------------------------------------------
//�X�^�[�g
void PlayScene::Start(float deltatime) {

	if (!_switch || count >= 5) { return; }

	count += deltatime;

	if (count < 3) {

		DrawFormatString(0, 0, -1, "��[���@%f", count);
		return;
	}

	if (count < 5) {
		DrawString(0, 0, "�X�^�[�g", -1);
		_start_flag = true;
		return;
	}
}


//----------------------------------------------------------------------------------------------------
//�Z�[�u
void PlayScene::SavePlayer() {

	FILE* fp = nullptr;

	fopen_s(&fp, "player.bin", "wb");

	fwrite(Pp->name, sizeof(Pp->name), 1, fp);
	fwrite(&Pp->sta, sizeof(CharaObj::Status), 1, fp);

	fclose(fp);
}


//----------------------------------------------------------------------------------------------------
//�Q�[���I�[�o�[
void PlayScene::isOver() {

	if (Pp->sta.HP == 0 || Ep->sta.HP == 0) {

		GMp->SRp->_switch = true;
	}
}


//----------------------------------------------------------------------------------------------------
//�����蔻��
void PlayScene::isHit() {

	for (auto p : Bp) {
		if (p->_team) {
			if (CircleHit(Ep->pos.x, Ep->pos.y, Ep->r, p->pos.x, p->pos.y, p->r)) {
				Ep->sta.HP--;
				p->alive_flag = false;
			}
		}
		else if (!p->_team) {
			if (CircleHit(Pp->pos.x, Pp->pos.y, Pp->r, p->pos.x, p->pos.y, p->r)) {
				Pp->sta.HP--;
				p->alive_flag = false;
			}
		}
	}
}


//----------------------------------------------------------------------------------------------------
//�e�쐬
void PlayScene::MakeBullet(t2k::Vector3 pos, float direction_x, float direction_y, bool t) {

	Bullet* bp = new Bullet(pos.x, pos.y, direction_x, direction_y, t);
	Bp.emplace_back(bp);
	Op.emplace_back(bp);
}


//----------------------------------------------------------------------------------------------------
//�J�������l�������}�E�X���W�̎擾
t2k::Vector3 PlayScene::GetMousePosition() {

	int x, y;
	GetMousePoint(&x, &y);

	t2k::Vector3 pos = { 0,0,0 };

	//�J�������l��
	pos.x = x + cam.pos.x - (GameManager::SCREEN_W >> 1);
	pos.y = y + cam.pos.y - (GameManager::SCREEN_H >> 1);

	return pos;
}

//�J�������l���������W�̎擾
t2k::Vector3 PlayScene::FixPositionVector(t2k::Vector3 pos) {

	t2k::Vector3 pos_ = {
		pos.x - cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - cam.pos.y + (GameManager::SCREEN_H >> 1),
		0
	};

	return pos_;
}


//----------------------------------------------------------------------------------------------------
//������
void PlayScene::Init() {

	if (!_init) { return; }

	Pp = new Player();
	Op.emplace_back(Pp);

	Ep = new Enemy(1);
	Op.emplace_back(Ep);

	_init = false;
}


//----------------------------------------------------------------------------------------------------
//���t���[���Ăяo��
void PlayScene::Update(float deltatime) {

	Init();
	DrawBuckGround();

	Start(deltatime);

	for (auto p : Op) {

		if (p->alive_flag) { p->Update(deltatime); }
	}

	cam.update(deltatime, Pp->pos);

	isHit();
	Delete();

	isOver();
}
void PlayScene::Render(float deltatime) {

	for (auto p : Op) {

		if (p->alive_flag) { p->Render(&cam); }
	}
}

//----------------------------------------------------------------------------------------------------