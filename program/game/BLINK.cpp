#include "GameManager.h"
#include "BLINK.h"

extern GameManager* GMp;

//----------------------------------------------------------------------------------------------
//コンストラクタ

BLINK::BLINK() {

	scroll_img_close = GMp->loadGraph("graphics/scroll/BLINK_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/BLINK_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/BLINK.png"));

	cool_time = 0.0f;
}