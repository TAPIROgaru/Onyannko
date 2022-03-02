#include <math.h>

//--------------------------------------------------------------------------------------------------
//自作ファイル

#include "Collision.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	// 円と円の当たり判定

	bool isHit_CircleAndCircle(Vector2 cA_pos, float cA_r, Vector2 cB_pos, float cB_r) {

		float A = cA_pos.x - cB_pos.x;
		float B = cA_pos.y - cB_pos.y;

		float C = A * A + B * B;

		float andR = cA_r + cB_r;

		float _c = sqrtf(C);

		if (andR >= _c) {
			return true;
		}

		return false;
	}


	//----------------------------------------------------------------------------------------------
	// 線分と線分の当たり判定

	bool isHit_LineAndLine(Line first_line, Line second_line) {

		//first_line.start_posを始点、first_line.end_posを終点
		//としたときの線分のベクトルABの大きさ
		Vector2 AB = first_line.start_pos - first_line.end_pos;

		//first_line.start_posを始点、second_line.start_posを終点
		//としたときの線分のベクトルACの大きさ
		Vector2 AC = first_line.start_pos - second_line.start_pos;

		//first_line.start_posを始点、second_line.end_posを終点
		//としたときの線分のベクトルADの大きさ
		Vector2 AD = first_line.start_pos - second_line.end_pos;

		//外積
		float ABcrossAC = Vector2::CrossProduct(AB, AC);
		float ABcrossAD = Vector2::CrossProduct(AB, AD);

		//乗算結果が正ならまたがっていない
		if (ABcrossAC * ABcrossAD > 0) { return false; }

		//second_line.start_posを始点、second_line.end_posを終点
		//としたときの線分のベクトルCDの大きさ
		Vector2 CD = second_line.start_pos - second_line.end_pos;

		//second_line.start_posを始点、first_line.start_posを終点
		//としたときの線分のベクトルCDの大きさ
		Vector2 CA = second_line.start_pos - first_line.start_pos;

		//second_line.start_posを始点、first_line.end_posを終点
		//としたときの線分のベクトルCBの大きさ
		Vector2 CB = second_line.start_pos - first_line.end_pos;

		//外積
		float CDcrossCA = Vector2::CrossProduct(CD, CA);
		float CDcrossCB = Vector2::CrossProduct(CD, CB);

		//乗算結果が正ならまたがっていない
		if (CDcrossCA * CDcrossCB > 0) { return false; }


		return true;
	}


	//----------------------------------------------------------------------------------------------
	// 線分と矩形の当たり判定

	bool isHit_LineAndRectangle(Line line, Quadrilateral quad) {

		Line line_array[4] = { quad.upper_line,quad.right_line,quad.bottom_line,quad.left_line };

		for (int i = 0; i < 4; i++) {
			if (isHit_LineAndLine(line, line_array[i])) { return true; }
		}

		return false;
	}


	//----------------------------------------------------------------------------------------------
	// 矩形と矩形の当たり判定

	bool isHit_RectangleAndRectangle(Quadrilateral first_quad, Quadrilateral second_quad) {

		//四辺形を線分に分けて配列に格納
		Line first_quad_ine_array[4] = {
			first_quad.upper_line,first_quad.right_line,
			first_quad.bottom_line,first_quad.left_line
		};

		//四辺形を線分に分けて配列に格納
		Line second_quad_ine_array[4] = {
			second_quad.upper_line,second_quad.right_line,
			second_quad.bottom_line,second_quad.left_line
		};

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				if (isHit_LineAndLine(first_quad_ine_array[i], second_quad_ine_array[k])) {
					return true;
				}
			}
		}

		return false;
	}
}