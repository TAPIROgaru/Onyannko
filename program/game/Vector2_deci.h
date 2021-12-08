#pragma once

//--------------------------------------------------------------------------------------------------
//自作ファイル



//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	//X座標Y座標の管理
	class Vector2_deci {
	public:

		Vector2_deci() :
			x(0),
			y(0)
		{}

		Vector2_deci(float _x, float _y) :
			x(_x),
			y(_y)
		{}
		//↑これらは初期化の少し早い方法

		float x;
		float y;

		Vector2_deci operator +(Vector2_deci p) {

			return Vector2_deci(x + p.x, y + p.y);
		}

		Vector2_deci operator -(Vector2_deci p) {

			return Vector2_deci(x - p.x, y - p.y);
		}

		bool operator ==(Vector2_deci p) {

			if (x == p.x && y == p.y) { return true; }
			return false;
		}
	};
}