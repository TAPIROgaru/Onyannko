#include <math.h>

//--------------------------------------------------------------------------------------------------
//����t�@�C��

#include "Collision.h"


//--------------------------------------------------------------------------------------------------

namespace tpr {

	//----------------------------------------------------------------------------------------------
	// �~�Ɖ~�̓����蔻��

	bool isHit_CircleAndCircle(Vector2 cA_pos, float cA_r, Vector2 cB_pos, float cB_r) {

		float A = cA_pos.x - cB_pos.x;
		float B = cA_pos.y - cB_pos.y;

		float C = A * A + B * B;

		float andR = cA_r + cB_r;

		float _c = sqrt(C);

		if (andR >= _c) {
			return true;
		}

		return false;
	}


	//----------------------------------------------------------------------------------------------
	// �����Ɛ����̓����蔻��

	bool isHit_LineAndLine(Line first_line, Line second_line) {

		//first_line.start_pos���n�_�Afirst_line.end_pos���I�_
		//�Ƃ����Ƃ��̐����̃x�N�g��AB�̑傫��
		Vector2 AB = first_line.start_pos - first_line.end_pos;

		//first_line.start_pos���n�_�Asecond_line.start_pos���I�_
		//�Ƃ����Ƃ��̐����̃x�N�g��AC�̑傫��
		Vector2 AC = first_line.start_pos - second_line.start_pos;

		//first_line.start_pos���n�_�Asecond_line.end_pos���I�_
		//�Ƃ����Ƃ��̐����̃x�N�g��AD�̑傫��
		Vector2 AD = first_line.start_pos - second_line.end_pos;

		//�O��
		float ABcrossAC = Vector2::CrossProduct(AB, AC);
		float ABcrossAD = Vector2::CrossProduct(AB, AD);

		//��Z���ʂ����Ȃ�܂������Ă��Ȃ�
		if (ABcrossAC * ABcrossAD > 0) { return false; }

		//second_line.start_pos���n�_�Asecond_line.end_pos���I�_
		//�Ƃ����Ƃ��̐����̃x�N�g��CD�̑傫��
		Vector2 CD = second_line.start_pos - second_line.end_pos;

		//second_line.start_pos���n�_�Afirst_line.start_pos���I�_
		//�Ƃ����Ƃ��̐����̃x�N�g��CD�̑傫��
		Vector2 CA = second_line.start_pos - first_line.start_pos;

		//second_line.start_pos���n�_�Afirst_line.end_pos���I�_
		//�Ƃ����Ƃ��̐����̃x�N�g��CB�̑傫��
		Vector2 CB = second_line.start_pos - first_line.end_pos;

		//�O��
		float CDcrossCA = Vector2::CrossProduct(CD, CA);
		float CDcrossCB = Vector2::CrossProduct(CD, CB);

		//��Z���ʂ����Ȃ�܂������Ă��Ȃ�
		if (CDcrossCA * CDcrossCB > 0) { return false; }


		return true;
	}


	//----------------------------------------------------------------------------------------------
	// �����Ƌ�`�̓����蔻��

	bool isHit_LineAndRectangle(Line line, Quadrilateral quad) {

		//�l�ӌ`������ɕ����Ĕz��Ɋi�[
		Line line_array[4] = { 
			quad.upper_line,quad.right_line,
			quad.bottom_line,quad.left_line
		};

		for (int i = 0; i < 4; i++) {
			if (isHit_LineAndLine(line,line_array[i])) { return true; }
		}

		return false;
	}


	//----------------------------------------------------------------------------------------------
	// ��`�Ƌ�`�̓����蔻��

	bool isHit_RectangleAndRectangle(Quadrilateral first_quad, Quadrilateral second_quad) {

		//�l�ӌ`������ɕ����Ĕz��Ɋi�[
		Line first_quad_ine_array[4] = {
			first_quad.upper_line,first_quad.right_line,
			first_quad.bottom_line,first_quad.left_line 
		};

		//�l�ӌ`������ɕ����Ĕz��Ɋi�[
		Line second_quad_ine_array[4] = {
			second_quad.upper_line,second_quad.right_line,
			second_quad.bottom_line,second_quad.left_line
		};

		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 4; k++) {
				if (isHit_LineAndLine(first_quad_ine_array[i], second_quad_ine_array[k])) {
					return true;
				}
			}
		}

		return false;
	}
}