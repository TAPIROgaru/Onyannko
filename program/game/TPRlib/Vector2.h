#pragma once

//--------------------------------------------------------------------------------------------------
//自作ファイル

#include "Color.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {

	//float型の2次元座標
	class Vector2 {
	public:

		//-------------------------------------------------------------------------------------
		//コンストラクタ

		//=======================================================
		// 変数宣言のみ
		//=======================================================
		Vector2() :
			x(0),
			y(0)
		{}

		//=======================================================
		// 座標指定
		// 1. X座標
		// 2. Y座標
		//=======================================================
		Vector2(float _x, float _y) :
			x(_x),
			y(_y)
		{}


		//-------------------------------------------------------------------------------------
		//オペレータ

		Vector2 operator +(Vector2 p) {

			return Vector2(x + p.x, y + p.y);
		}

		Vector2 operator -(Vector2 p) {

			return Vector2(x - p.x, y - p.y);
		}

		Vector2 operator *(Vector2 p) {

			return Vector2(x * p.x, y * p.y);
		}

		Vector2 operator /(Vector2 p) {

			return Vector2(x / p.x, y / p.y);
		}

		Vector2 operator =(Vector2 p) {

			return Vector2(x = p.x, y = p.y);
		}

		Vector2 operator +(float value) {

			return Vector2(x + value, y + value);
		}

		Vector2 operator -(float value) {

			return Vector2(x - value, y - value);
		}

		Vector2 operator /(float value) {

			return Vector2(x / value, y / value);
		}

		Vector2 operator *(float value) {

			return Vector2(x * value, y * value);
		}

		Vector2 operator +=(Vector2 p) {

			return Vector2(x += p.x, y += p.y);
		}

		Vector2 operator -=(Vector2 p) {

			return Vector2(x -= p.x, y -= p.y);
		}

		Vector2 operator *=(Vector2 p) {

			return Vector2(x *= p.x, y *= p.y);
		}

		Vector2 operator /=(Vector2 p) {

			return Vector2(x /= p.x, y /= p.y);
		}

		bool operator ==(Vector2 p) {

			if (x == p.x && y == p.y) { return true; }
			return false;
		}


		//-------------------------------------------------------------------------------------
		//関数

		//=======================================================
		// 点の描画
		// 1. 色
		//=======================================================
		void DrawPoint(unsigned int color);

		//=======================================================
		// 点の描画
		// 1. 色
		//=======================================================
		void DrawPoint(Color c);

		//=======================================================
		// 内積
		// 1. ベクトルAの大きさ
		// 2. ベクトルBの大きさ
		// 
		// return 
		//=======================================================
		static float CrossProduct(Vector2 first_pos, Vector2 second_pos);

		//=======================================================
		// 外積
		// 1. 
		// 2. 
		// 
		// return 
		//=======================================================
		static Vector2 InnerProduct(Vector2 first_pos, Vector2 second_pos);

		//=======================================================
		// 2点間の距離の計算
		// 1. 始点
		// 2. 終点
		// 
		// return 距離
		//=======================================================
		static float DistanceCalc(Vector2 start_pos, Vector2 end_pos);

		//=======================================================
		// 2点間の中心点の計算
		// 1. 始点
		// 2. 終点
		// 
		// return 中心点
		//=======================================================
		static Vector2 CenterPointCalc(Vector2 start_pos, Vector2 end_pos);


		//-------------------------------------------------------------------------------------
		//変数

		float x;
		float y;
	};
}