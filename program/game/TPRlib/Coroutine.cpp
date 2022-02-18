#include "Coroutine.h"
#include "DxLib.h"

namespace tpr {


	void Coroutine::UpDate(float deltatime) {

		if (TimeKeeper(deltatime)) {
			(*func)();
			_delete_flag = true;
		}
	}


	bool Coroutine::TimeKeeper(float deltatime) {

		count += deltatime;
		DrawFormatString(0, 50, -1, "%f", count);

		if (count < time) {
			return false;
		}

		return true;
	}
}