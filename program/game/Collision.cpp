#include <math.h>

//--------------------------------------------------------------------------------------------------
//自作ファイル

#include "Collision.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	// 円と円の当たり判定

	bool isHit_CircleAndCircle(Vector2_deci cA_pos, float cA_r, Vector2_deci cB_pos, float cB_r){

		float A = cA_pos.x - cB_pos.x;
		float B = cA_pos.y - cB_pos.y;

		float C = A * A + B * B;

		float andR = cA_r + cB_r;

		float _c = sqrt(C);

		if (andR >= _c) {
			return true;
		}

		return false;
	}


	//----------------------------------------------------------------------------------------------
	// 線分と線分の当たり判定
}