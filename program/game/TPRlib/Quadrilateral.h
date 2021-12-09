#pragma once
#include "DxLib.h"

//---------------------------------------------------------------------------------------------
//自作ファイル

#include "Line.h"


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
			D_pos(0,0),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// 矩形の場合(2点指定)
		// 1. 左上の座標
		// 2. 右下の座標
		//=======================================================
		Quadrilateral(Vector2 upper_left_pos, Vector2 bottom_right_pos) :

			A_pos(upper_left_pos),
			B_pos(bottom_right_pos.x ,upper_left_pos.y),
			C_pos(bottom_right_pos),
			D_pos(upper_left_pos.x ,bottom_right_pos.y),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// 矩形の場合(中心とサイズ)
		// 1. 中心座標
		// 2. 幅
		// 3. 高さ
		//=======================================================
		Quadrilateral(Vector2 pos, int size_w, int size_h) :

			A_pos(pos.x - (size_w >> 1), pos.y - (size_h >> 1)),
			B_pos(pos.x + (size_w >> 1), pos.y - (size_h >> 1)),
			C_pos(pos.x + (size_w >> 1), pos.y + (size_h >> 1)),
			D_pos(pos.x - (size_w >> 1), pos.y + (size_h >> 1)),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// 四辺形の場合(4点指定)
		// 1. 左上の座標
		// 2. 右上の座標
		// 3. 右下の座標
		// 4. 左下の座標
		//=======================================================
		Quadrilateral(
			Vector2 upper_left_pos, Vector2 upper_right_pos,
			Vector2 bottom_left_pos, Vector2 bottom_right_pos):

			A_pos(upper_left_pos),
			B_pos(upper_right_pos),
			C_pos(bottom_right_pos),
			D_pos(bottom_left_pos),
			upper_line(A_pos,B_pos),
			right_line(B_pos,C_pos),
			bottom_line(C_pos,D_pos),
			left_line(D_pos,A_pos)
		{}

		//-------------------------------------------------------------------------------------
		//オペレータ

		Quadrilateral operator = (const Quadrilateral quad) {

			return Quadrilateral(
				A_pos = quad.A_pos,
				B_pos = quad.B_pos,
				C_pos = quad.C_pos,
				D_pos = quad.D_pos
			);
		}


		//-------------------------------------------------------------------------------------
		//関数

		void DrawBox() {

			upper_line.DrawLine();
			bottom_line.DrawLine();
			left_line.DrawLine();
			right_line.DrawLine();
		}


		//-------------------------------------------------------------------------------------
		//変数

		Vector2 A_pos; //左上
		Vector2 B_pos; //右上
		Vector2 C_pos; //右下
		Vector2 D_pos; //左下

		Line upper_line;    //上辺
		Line bottom_line;   //底辺
		Line left_line;     //左辺
		Line right_line;    //右辺
	};
}