#include "GameManager.h"
#include "KUNAI.h"

extern GameManager* GMp;


KUNAI::KUNAI() {

	scroll_img_close = GMp->loadGraph("graphics/scroll/KUNAI_close.png");
	scroll_img_open = GMp->loadGraph("graphics/scroll/KUNAI_open.png");

	skill_img.emplace_back(GMp->loadGraph("graphics/NINGU/KUNAI.png"));

	cool_time = 0.0f;
}
void KUNAI::Active(tpr::Vector2 pos, float dire_x, float dire_y)
{

}