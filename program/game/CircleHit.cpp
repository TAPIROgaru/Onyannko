#include "CircleHit.h"

#include <math.h>

bool CircleHit(float pos1_x, float pos1_y, int r1, float pos2_x, float pos2_y, int r2) {

	float A = pos1_x - pos2_x;
	float B = pos1_y - pos2_y;

	float C = A * A + B * B;

	int andR = r1 + r2;

	float _c = sqrt(C);

	if (andR >= _c) {
		return true;
	}

	return false;
}