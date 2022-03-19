#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL {
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x * x + y * y);
	}

	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x * x + y * y);
		float angle = acos(x / d);

		if (y > 0) angle = PI_2 - angle;

		return angle;
	}

	void log(string tag, string log)
	{
		//if (tag == DEBUG_ALL_TAG || tag == DEBUG_MY_TAG) {
		if(true) {
			cout.setf(ios::left);
			cout << setw(15) << tag << " : ";
			cout << log << endl;
		}
	}
}