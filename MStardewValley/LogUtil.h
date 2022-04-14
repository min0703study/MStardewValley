#pragma once
namespace LOG
{
	inline void tag(string tag) {
		cout << "[" << setw(7) << tag  << "] ";

	}
	inline void d(string log)
	{
#if DEBUG_MODE
		LOG::tag(LOG_DEFAULT_TAG);
		cout.setf(ios::left);
		cout << log << endl;
#endif
	}

	inline void d_blue(string tag, string log)
	{
#if DEBUG_MODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout.setf(ios::left);
		LOG::tag(tag);
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	}

	inline void d_blue(string log)
	{
#if DEBUG_MODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout.setf(ios::left);
		LOG::tag(LOG_DEFAULT_TAG);
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	}

	inline void d(string tag, string log)
	{
#if DEBUG_MODE
		if (tag == LOG_KEYMNG_TAG) return;
		cout.setf(ios::left);
		LOG::tag(tag);
		cout << log << endl;
#endif
	}

	inline void e(string log)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout.setf(ios::left);
		LOG::tag(LOG_DEFAULT_TAG);
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	inline void e(string tag, string log)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout.setf(ios::left);
		LOG::tag(tag);
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	inline void w(string log)
	{
#if DEBUG_MODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cout.setf(ios::left);
		LOG::tag(LOG_DEFAULT_TAG);
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	}

	inline void w(string tag, string log)
	{
#if DEBUG_MODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cout.setf(ios::left);
		LOG::tag(tag);
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	}


	inline void r(string log)
	{

	}
}