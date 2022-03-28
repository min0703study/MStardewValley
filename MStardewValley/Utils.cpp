#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL {
	void log(string tag, string log)
	{
		//if (tag == DEBUG_ALL_TAG || tag == DEBUG_MY_TAG) {
		if(true) {
			cout.setf(ios::left);
			cout << setw(15) << tag << " : ";
			cout << log << endl;
		}
	}
	void log(string log)
	{
		MY_UTIL::log(DEBUG_ALL_TAG, log);
	}
}