#include "GameManager.h"
#include "KAGINAWA.h"

extern GameManager* GMp;


//----------------------------------------------------------------------------------------------
//コンストラクタ
KAGINAWA::KAGINAWA(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KAGINAWA_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KAGINAWA_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KAGINAWA.png"));

	cool_time = 0.0f;
	this->angle = angle;
}
void KAGINAWA::Active(tpr::Vector2 pos, float dire_x, float dire_y)
{

}