#include "GameManager.h"
#include "KAGINAWA.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------
//コンストラクタ
KAGINAWA::KAGINAWA() {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KAGINAWA_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KAGINAWA_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAGINAWA.png"));

	cool_time = 0.0f;
}