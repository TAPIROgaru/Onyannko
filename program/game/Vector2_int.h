#pragma once

//--------------------------------------------------------------------------------------------------
//自作ファイル



//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	//X座標Y座標の管理
	class Vector2_int {
	public:

		Vector2_int() :
			x(0),
			y(0)
		{}

		Vector2_int(int _x, int _y) :
			x(_x),
			y(_y)
		{}
		//↑これらは初期化の少し早い方法

		int x;
		int y;

		Vector2_int operator +(Vector2_int p) {

			return Vector2_int(x + p.x, y + p.y);
		}

		Vector2_int operator -(Vector2_int p) {

			return Vector2_int(x - p.x, y - p.y);
		}

		bool operator ==(Vector2_int p) {

			if (x == p.x && y == p.y) { return true; }
			return false;
		}
	};
}