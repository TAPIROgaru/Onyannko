#include "DxLib.h"
#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------------------------
//����t�@�C��
#include "Vector2.h"
#include "Angle.h"

namespace tpr {

	//-----------------------------------------------------------------------------------------
	// �_�̕`��

	void Vector2::DrawPoint(unsigned int c){
			DrawPixel((int)x, (int)y, c);
	}

	//-----------------------------------------------------------------------------------------
	// �_�̕`��

	void Vector2::DrawPoint(Color c) {
		DrawPixel((int)x, (int)y, c.GetColor());
	}

	//-----------------------------------------------------------------------------------------
	//�O��
	
	float Vector2::CrossProduct(Vector2 first_pos, Vector2 second_pos) {

		return float((first_pos.x * second_pos.y) - (first_pos.y * second_pos.x));
	}


	//-----------------------------------------------------------------------------------------
	// 2�_�Ԃ̋����̌v�Z

	float Vector2::DistanceCalc(Vector2 start_pos, Vector2 end_pos) {

		float x = end_pos.x - start_pos.x;

		float y = end_pos.y - start_pos.y;

		float dist = sqrtf(x * x + y * y);

		return dist;
	}


	//-----------------------------------------------------------------------------------------
	// 2�_�Ԃ̒��S�_�̌v�Z

	Vector2 Vector2::CenterPointCalc(Vector2 start_pos, Vector2 end_pos) {

		Vector2 pos;

		pos = (end_pos - start_pos) / 2 + start_pos;

		return pos;
	}
}