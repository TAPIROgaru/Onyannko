//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Line.h"

//---------------------------------------------------------------------------------------------

namespace tpr {

	//-----------------------------------------------------------------------------------------
	// ���̕`��

	void Line::DrawLine(unsigned int c) {
		DxLib::DrawLine(
			(int)start_pos.x, (int)start_pos.y,
			(int)end_pos.x, (int)end_pos.y,
			c);
	}

	void Line::DrawLine(Color c) {
		DxLib::DrawLine(
			(int)start_pos.x, (int)start_pos.y,
			(int)end_pos.x, (int)end_pos.y,
			c.GetColor());
	}
}