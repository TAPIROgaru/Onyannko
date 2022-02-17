#include "GameManager.h"
#include "KUNAI.h"

extern GameManager* GMp;


KUNAI::KUNAI(tpr::Vector2 pos_, int angle) {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KUNAI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KUNAI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KUNAI.png"));

	cool_time = 0.0f;
	this->angle = angle;
}
void KUNAI::Active(tpr::Vector2 pos, float dire_x, float dire_y)
{

}