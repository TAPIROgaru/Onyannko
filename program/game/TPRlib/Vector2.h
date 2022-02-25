#pragma once

//--------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Color.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {

	//float�^��2�������W
	class Vector2 {
	public:

		//-------------------------------------------------------------------------------------
		//�R���X�g���N�^

		//=======================================================
		// �ϐ��錾�̂�
		//=======================================================
		Vector2() :
			x(0),
			y(0)
		{}

		//=======================================================
		// ���W�w��
		// 1. X���W
		// 2. Y���W
		//=======================================================
		Vector2(float _x, float _y) :
			x(_x),
			y(_y)
		{}


		//-------------------------------------------------------------------------------------
		//�I�y���[�^

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
		//�֐�

		//=======================================================
		// �_�̕`��
		// 1. �F
		//=======================================================
		void DrawPoint(unsigned int color);

		//=======================================================
		// �_�̕`��
		// 1. �F
		//=======================================================
		void DrawPoint(Color c);

		//=======================================================
		// ����
		// 1. �x�N�g��A�̑傫��
		// 2. �x�N�g��B�̑傫��
		// 
		// return 
		//=======================================================
		static float CrossProduct(Vector2 first_pos, Vector2 second_pos);

		//=======================================================
		// �O��
		// 1. 
		// 2. 
		// 
		// return 
		//=======================================================
		static Vector2 InnerProduct(Vector2 first_pos, Vector2 second_pos);

		//=======================================================
		// 2�_�Ԃ̋����̌v�Z
		// 1. �n�_
		// 2. �I�_
		// 
		// return ����
		//=======================================================
		static float DistanceCalc(Vector2 start_pos, Vector2 end_pos);

		//=======================================================
		// 2�_�Ԃ̒��S�_�̌v�Z
		// 1. �n�_
		// 2. �I�_
		// 
		// return ���S�_
		//=======================================================
		static Vector2 CenterPointCalc(Vector2 start_pos, Vector2 end_pos);


		//-------------------------------------------------------------------------------------
		//�ϐ�

		float x;
		float y;
	};
}