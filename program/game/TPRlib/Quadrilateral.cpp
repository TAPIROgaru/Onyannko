//---------------------------------------------------------------------------------------------
//����t�@�C��

#include "Quadrilateral.h"

//---------------------------------------------------------------------------------------------

namespace tpr {

	//-----------------------------------------------------------------------------------------
	// �l�ӌ`�̕`��

	void Quadrilateral::DrawBox(unsigned int c) {

		upper_line.DrawLine(c);
		bottom_line.DrawLine(c);
		left_line.DrawLine(c);
		right_line.DrawLine(c);
	}

	void Quadrilateral::DrawBox(Color c) {

		upper_line.DrawLine(c);
		bottom_line.DrawLine(c);
		left_line.DrawLine(c);
		right_line.DrawLine(c);
	}
}