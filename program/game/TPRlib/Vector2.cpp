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

	void Vector2::DrawPoint(unsigned int c){
			DrawPixel((int)x, (int)y, c);
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

	float Vector2::DistanceCalc(Vector2 start_pos, Vector2 end_pos) {

		float x = end_pos.x - start_pos.x;

		float y = end_pos.y - start_pos.y;

		float dist = sqrtf(x * x + y * y);

		return dist;
	}


	//-----------------------------------------------------------------------------------------
	// ベクトルの正規化

	Vector2 Vector2::Normalize(Vector2 start_pos, Vector2 end_pos) {

		Vector2 pos = end_pos - start_pos;

		float magnitude = sqrtf(pos.x * pos.x + pos.y * pos.y);

		Vector2 dire = pos / magnitude;

		return dire;
	}


	//-----------------------------------------------------------------------------------------
	// 2点間の中心点の計算

	Vector2 Vector2::CenterPointCalc(Vector2 start_pos, Vector2 end_pos) {

		Vector2 pos;

		pos = (end_pos - start_pos) / 2 + start_pos;

		return pos;
	}
}