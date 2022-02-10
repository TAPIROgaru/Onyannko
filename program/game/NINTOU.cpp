#include "NINTOU.h"

void NINTOU::Active(tpr::Vector2 pos, float dire_x, float dire_y) {

	int i = 0;
	DrawGraph(pos.x + dire_x * 100, pos.y + dire_y * 100, skill_img[i], true);
	i++;
	_active = true;
	if (i > skill_img.size()) { _active = false; }
}