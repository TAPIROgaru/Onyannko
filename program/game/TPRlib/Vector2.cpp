#include "DxLib.h"
#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------------------------
//自作ファイル
#include "Vector2.h"
#include "Angle.h"

namespace tpr {

	//-----------------------------------------------------------------------------------------
	// 点の描画

	void Vector2::DrawPoint(unsigned int color){
			DrawPixel((int)x, (int)y, color);
	}

	//-----------------------------------------------------------------------------------------
	// 点の描画

	void Vector2::DrawPoint(Color c) {
		DrawPixel((int)x, (int)y, c.GetColor());
	}

	//-----------------------------------------------------------------------------------------
	//外積
	
	float Vector2::CrossProduct(Vector2 first_pos, Vector2 second_pos) {

		return float((first_pos.x * second_pos.y) - (first_pos.y * second_pos.x));
	}


	//-----------------------------------------------------------------------------------------
	// 2点間の距離の計算

	int Vector2::DistanceCalc(Vector2 start_pos, Vector2 end_pos) {

		int dist;

		float rad = Angle::RadCalc(start_pos, end_pos);

		dist = (int)((start_pos - end_pos).x / cosf(rad));

		return dist;
	}


	//-----------------------------------------------------------------------------------------
	// 2点間の中心点の計算

	Vector2 Vector2::CenterPointCalc(Vector2 start_pos, Vector2 end_pos) {

		Vector2 pos;

		pos = (end_pos - start_pos) / 2 + start_pos;

		return pos;
	}
}