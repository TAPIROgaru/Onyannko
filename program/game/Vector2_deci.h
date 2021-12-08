#pragma once

//--------------------------------------------------------------------------------------------------
//����t�@�C��



//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	//X���WY���W�̊Ǘ�
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
		//�������͏������̏����������@

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