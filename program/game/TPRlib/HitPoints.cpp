

//----------------------------------------------------------------------------------------------
//����t�@�C��

#include "HitPoints.h"
#include "Quadrilateral.h"


//----------------------------------------------------------------------------------------------

namespace tpr {

	void Hitpoints::DrawGauge(Vector2 pos, int c, float max, float now) {

		if (max < now)now = max;
		if (now < 0)now = 0.0;

		Quadrilateral quad(pos, size_w, size_h);
		quad.DrawBox(c);

		int x1 = (int)(pos.x - size_w / 2 + 1);
		int x2 = (int)(pos.x + size_w / 2);
		int y1 = (int)(pos.y - size_h / 2 + 1);
		int y2 = (int)(pos.y + size_h / 2);

		float ratio = now / max;

		if (ratio == 1) {

			DrawBox(x1, y1, x2, y2, GetColor(0, 255, 0), true);
		}
		else if (ratio == 0) {

			DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), true);
		}
		else {

			int w = (int)(size_w * ratio);

			DrawBox(x1, y1, x1 + w, y2, GetColor(0, 255, 0), true);

			DrawBox(x1 + w, y1, x2, y2, GetColor(255, 0, 0), true);
		}
	}
}