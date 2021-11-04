#include"GameManager.h"


//----------------------------------------------------------------------------------------------------
//コンストラクタ
GameManager::GameManager() {

	img = LoadGraph("graphics/sample.jpg");

	STp = new TitleScene();
	Sp.emplace_back(STp);
}



//----------------------------------------------------------------------------------------------------
//背景
void GameManager::DrawBuckGround() {

	for (int y = -FIELD_H; y < FIELD_H; y += 16) {
		for (int x = -FIELD_W; x < FIELD_W; x += 16) {

			DrawGraph(x, y, img, false);
		}
	}
}


//----------------------------------------------------------------------------------------------------
//カメラを考慮したマウス座標の取得
t2k::Vector3 GameManager::GetMousePosition() {

	int x, y;
	GetMousePoint(&x, &y);

	t2k::Vector3 pos = { 0,0,0 };

	//カメラを考慮
	pos.x = x + SPp->cam.pos.x - (GameManager::SCREEN_W >> 1);
	pos.y = y + SPp->cam.pos.y - (GameManager::SCREEN_H >> 1);

	return pos;
}

//カメラを考慮した座標の取得
t2k::Vector3 GameManager::FixPositionVector(t2k::Vector3 pos) {

	t2k::Vector3 pos_ = {
		pos.x - SPp->cam.pos.x + (GameManager::SCREEN_W >> 1),
		pos.y - SPp->cam.pos.y + (GameManager::SCREEN_H >> 1),
		0
	};

	return pos_;
}



//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void GameManager::Update(float deltatime) {

	for (auto pointer : Sp) {

		pointer->Update(deltatime);
	}
}
void GameManager::Render(float deltatime) {

	t2k::Vector3 pos_1 = FixPositionVector(img_pos1);
	t2k::Vector3 pos_2 = FixPositionVector(img_pos2);

	//DrawBuckGround();
	DrawExtendGraph(pos_1.x,pos_1.y,pos_2.x,pos_2.y,img,true);


	for (auto pointer : Sp) {

		pointer->Render();
	}

}
//----------------------------------------------------------------------------------------------------