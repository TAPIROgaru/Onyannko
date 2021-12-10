#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------------------------
//自作ファイル

#include "Rotation.h"
#include "Angle.h"


namespace tpr {

	//-----------------------------------------------------------------------------------------
	// 回転座標を得る

	Vector2 Rotation::RotaVec2(Vector2 pos, Vector2 origin_pos, float rad) {

		Vector2 _pos = pos - origin_pos;
		Vector2 rota_pos;

		rota_pos.x = _pos.x * cosf(rad) - _pos.y * sinf(rad);
		rota_pos.y = _pos.x * sinf(rad) + _pos.y * cosf(rad);

		return rota_pos + origin_pos;
	}
}