#pragma once
#include "DxLib.h"

//---------------------------------------------------------------------------------------------
//自作ファイル

#include "Line.h"
#include "Rotation.h"
#include "Angle.h"
#include "Color.h"


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
			A_pos(0, 0),
			B_pos(0, 0),
			C_pos(0, 0),
			D_pos(0, 0),
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
			B_pos(bottom_right_pos.x, upper_left_pos.y),
			C_pos(bottom_right_pos),
			D_pos(upper_left_pos.x, bottom_right_pos.y),
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
		// 矩形の場合(中心座標とサイズと回転)
		// 1. 中心座標
		// 2. 幅
		// 3. 高さ
		// 4. 回転(ラジアン)
		//=======================================================
		Quadrilateral(Vector2 pos, int size_w, int size_h, float rad) :

			A_pos(Rotation::RotaVec2(Vector2(pos.x - (size_w >> 1), pos.y - (size_h >> 1)), pos, rad)),
			B_pos(Rotation::RotaVec2(Vector2(pos.x + (size_w >> 1), pos.y - (size_h >> 1)), pos, rad)),
			C_pos(Rotation::RotaVec2(Vector2(pos.x + (size_w >> 1), pos.y + (size_h >> 1)), pos, rad)),
			D_pos(Rotation::RotaVec2(Vector2(pos.x - (size_w >> 1), pos.y + (size_h >> 1)), pos, rad)),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//=======================================================
		// 矩形の場合(軸になる2点とサイズ)
		// 1. 始点
		// 2. 終点
		// 3. 幅
		//=======================================================
		Quadrilateral(Vector2 start_pos, Vector2 end_pos, int size_w) {

			Vector2 pos_c = Vector2::CenterPointCalc(start_pos, end_pos);

			int size_h = Vector2::DistanceCalc(start_pos, end_pos);

			float rad = Angle::RadCalc(start_pos, end_pos) + Angle::DegChangeRad(90);

			*this = Quadrilateral(pos_c, size_w, size_h, rad);

			upper_line = Line(A_pos, B_pos);
			right_line = Line(B_pos, C_pos);
			bottom_line = Line(C_pos, D_pos);
			left_line = Line(D_pos, A_pos);
		}

		//=======================================================
		// 四辺形の場合(4点指定)
		// 1. 左上の座標
		// 2. 右上の座標
		// 3. 右下の座標
		// 4. 左下の座標
		//=======================================================
		Quadrilateral(
			Vector2 upper_left_pos, Vector2 upper_right_pos,
			Vector2 bottom_left_pos, Vector2 bottom_right_pos) :

			A_pos(upper_left_pos),
			B_pos(upper_right_pos),
			C_pos(bottom_right_pos),
			D_pos(bottom_left_pos),
			upper_line(A_pos, B_pos),
			right_line(B_pos, C_pos),
			bottom_line(C_pos, D_pos),
			left_line(D_pos, A_pos)
		{}

		//-------------------------------------------------------------------------------------
		//オペレータ

		inline Quadrilateral operator = (const Quadrilateral p) {

			return Quadrilateral(
				A_pos = p.A_pos,
				B_pos = p.B_pos,
				C_pos = p.C_pos,
				D_pos = p.D_pos
			);
		}


		//-------------------------------------------------------------------------------------
		//関数

		//=======================================================
		// 箱の描画
		// 1. 色
		//=======================================================
		void DrawBox(unsigned int c);

		//=======================================================
		// 箱の描画
		// 1. 色
		//=======================================================
		void DrawBox(Color c);

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