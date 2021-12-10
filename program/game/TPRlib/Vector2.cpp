#include "DxLib.h"

#include "Vector2.h"

namespace tpr {

	void Vector2::DrawPoint(){
			DrawPixel((int)x, (int)y, -1);
	}


	//äOêœ
	
	float Vector2::CrossProduct(Vector2 first_pos, Vector2 second_pos) {

		return float((first_pos.x * second_pos.y) - (first_pos.y * second_pos.x));
	}

}