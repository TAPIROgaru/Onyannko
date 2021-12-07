#pragma once

//--------------------------------------------------------------------------------------------------
//自作ファイル



//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	//X座標Y座標の管理
	class Vector2 {
	public:

		Vector2() :
			x(0),
			y(0)
		{}

		Vector2(int _x, int _y) :
			x(_x),
			y(_y)
		{}
		//↑これらは初期化の少し早い方法

		int x;
		int y;

		Vector2 operator +(Vector2 p) {

			return Vector2(x + p.x, y + p.y);
		}

		Vector2 operator -(Vector2 p) {

			return Vector2(x - p.x, y - p.y);
		}

		bool operator ==(Vector2 p) {

			if (x == p.x && y == p.y) { return true; }
			return false;
		}
	};
}