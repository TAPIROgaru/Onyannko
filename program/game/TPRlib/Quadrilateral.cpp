//---------------------------------------------------------------------------------------------
//自作ファイル

#include "Quadrilateral.h"

//---------------------------------------------------------------------------------------------

namespace tpr {

	//-----------------------------------------------------------------------------------------
	// 四辺形の描画

	void Quadrilateral::DrawBox(unsigned int c) {

		//upper_line.DrawLine(c);
		bottom_line.DrawLine(c);
		left_line.DrawLine(c);
		right_line.DrawLine(c);
	}

	void Quadrilateral::DrawBox(Color c) {

		//upper_line.DrawLine(c);
		bottom_line.DrawLine(c);
		left_line.DrawLine(c);
		right_line.DrawLine(c);
	}
}