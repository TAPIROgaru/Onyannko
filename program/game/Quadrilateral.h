#pragma once
#include "DxLib.h"

//---------------------------------------------------------------------------------------------
//自作ファイル

#include "Vector2_deci.h"


//---------------------------------------------------------------------------------------------

namespace tpr {

	// 四辺形
	class Quadrilateral {

	public:

		//-------------------------------------------------------------------------------------
		//コンストラクタ

		//=======================================================
		// 変数宣言のみ
		//=======================================================
		Quadrilateral() :
			A_pos(0,0),
			B_pos(0,0),
			C_pos(0,0),
			D_pos(0,0)
		{}

		//=======================================================
		// 矩形の場合(2点指定)
		// 1. 左上の座標
		// 2. 右下の座標
		//=======================================================
		Quadrilateral(Vector2_deci upper_left_pos, Vector2_deci bottom_right_pos) :
			A_pos(upper_left_pos),
			B_pos(Vector2_deci{ bottom_right_pos.x ,upper_left_pos.y }),
			C_pos(bottom_right_pos),
			D_pos(Vector2_deci{ upper_left_pos.x ,bottom_right_pos.y })
		{}

		//=======================================================
		// 四辺形の場合(4点指定)
		// 1. 左上の座標
		// 2. 右上の座標
		// 3. 右下の座標
		// 4. 左下の座標
		//=======================================================
		Quadrilateral(
			Vector2_deci upper_left_pos, Vector2_deci upper_right_pos,
			Vector2_deci bottom_left_pos, Vector2_deci bottom_right_pos):

			A_pos(upper_left_pos),
			B_pos(upper_right_pos),
			C_pos(bottom_right_pos),
			D_pos(bottom_left_pos)
		{}

		//-------------------------------------------------------------------------------------
		//関数

		void DrawBox() {

			DrawLine((int)A_pos.x, (int)A_pos.y, (int)B_pos.x, (int)B_pos.y, -1);
			DrawLine((int)B_pos.x, (int)B_pos.y, (int)C_pos.x, (int)C_pos.y, -1);
			DrawLine((int)C_pos.x, (int)C_pos.y, (int)D_pos.x, (int)D_pos.y, -1);
			DrawLine((int)D_pos.x, (int)D_pos.y, (int)A_pos.x, (int)A_pos.y, -1);
		}

		//-------------------------------------------------------------------------------------
		//変数

		Vector2_deci A_pos; //左上
		Vector2_deci B_pos; //右上
		Vector2_deci C_pos; //右下
		Vector2_deci D_pos; //左下
	};
}