#include <stdio.h>
#include <math.h>


//---------------------------------------------------------------------------------------------
//����t�@�C��
#include "Angle.h"

#define PI 3.14159265359


namespace tpr {

	//-----------------------------------------------------------------------------------------
	// ��_�Ԃ̊p�x���v�Z

	float Angle::RadCalc(Vector2 start_pos, Vector2 end_pos) {

		Vector2 pos_ = end_pos - start_pos;

		return atanf(pos_.y / pos_.x) * -1;
	}

	//-----------------------------------------------------------------------------------------
	// ��_�Ԃ̊p�x���v�Z

	int Angle::DegCalc(Vector2 start_pos, Vector2 end_pos) {

		return RadChangeDeg(RadCalc(start_pos, end_pos));
	}


	//-----------------------------------------------------------------------------------------
	// �x���@���ʓx�@�ɒ���

	float Angle::DegChangeRad(int degree) {

		float rad;

		rad = degree * PI / 180 * -1;

		return rad;
	}


	//-----------------------------------------------------------------------------------------
	// �ʓx�@��x���@�ɒ���

	int Angle::RadChangeDeg(float radian) {

		int deg;

		deg = radian / PI * 180 * -1;

		return deg;
	}


	//-----------------------------------------------------------------------------------------
	// �_A�𒆐S��X��Y���ŕ��������Ƃ��_B���ǂ��ɂ��邩

	inline int Angle::SearchSide(Vector2 start_pos, Vector2 end_pos) {

		const int ON_AXIS = 0;
		const int UPPER_RIGHT = 1;
		const int UPPER_LEFT = 2;
		const int BOTTON_RIGHT = 3;
		const int BOTTON_LEFT = 4;

		if (start_pos.x == end_pos.x) { return ON_AXIS; }
		if (start_pos.y == end_pos.y) { return ON_AXIS; }

		Vector2 pos_ = end_pos - start_pos;

		if (pos_.x > 0 && pos_.y > 0) { return UPPER_RIGHT; }
		if (pos_.x < 0 && pos_.y > 0) { return UPPER_LEFT; }
		if (pos_.x < 0 && pos_.y < 0) { return BOTTON_RIGHT; }
		if (pos_.x > 0 && pos_.y < 0) { return BOTTON_LEFT; }
	}
}