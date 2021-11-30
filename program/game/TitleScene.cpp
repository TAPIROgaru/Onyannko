#include "DxLib.h"

#include "TitleScene.h"
#include "GameManager.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------------
//コンストラクタ
TitleScene::TitleScene() {


}


//----------------------------------------------------------------------------------------------------
//
void TitleScene::ChangeMenuScene() {

	if (false == (GetMouseInput() & MOUSE_INPUT_LEFT)) { return; }

	int m_x, m_y;
	GetMousePoint(&m_x, &m_y);

	if ((m_x > x1 && m_x < x2) && (m_y > y1 && m_y < y2)) {

		_switch = false;
		GMp->SMp->_switch = true;
	}
}


//----------------------------------------------------------------------------------------------------
//毎フレーム呼び出し

void TitleScene::Update(float deltatime) {

	ChangeMenuScene();
}
void TitleScene::Render(float deltatime) {

	DrawBox(x1, y1, x2, y2, -1, false);
	DrawString(480, 200, "タイトル", -1);

}

//----------------------------------------------------------------------------------------------------