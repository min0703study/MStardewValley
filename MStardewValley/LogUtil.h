#pragma once
namespace LOG
{
	inline void d(string log)
	{
#ifdef DEBUG_MODE
		cout.setf(ios::left);
		cout << setw(15) << LOG_DEFAULT_TAG << " : ";
		cout << log << endl;
#endif
	}

	inline void d_blue(string tag, string log)
	{
#ifdef DEBUG_MODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout.setf(ios::left);
		cout << setw(15) << tag << " : ";
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	}

	inline void d_blue(string log)
	{
#ifdef DEBUG_MODE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout.setf(ios::left);
		cout << setw(15) << LOG_DEFAULT_TAG << " : ";
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	}

	inline void d(string tag, string log)
	{
#ifdef DEBUG_MODE
		cout.setf(ios::left);
		cout << setw(15) << tag << " : ";
		cout << log << endl;
#endif
	}

	inline void e(string log)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout.setf(ios::left);
		cout << setw(15) << LOG_DEFAULT_TAG << " : ";
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	inline void e(string tag, string log)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout.setf(ios::left);
		cout << setw(15) << tag << " : ";
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	inline void w(string log)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cout.setf(ios::left);
		cout << setw(15) << LOG_DEFAULT_TAG << " : ";
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	inline void w(string tag, string log)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		cout.setf(ios::left);
		cout << setw(15) << tag << " : ";
		cout << log << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}


	inline void r(string log)
	{

	}
}