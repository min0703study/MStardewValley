#include "Stdafx.h"

#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
	//! Do Noting
	return S_OK;
}

void JsonSaveLoader::release(void)
{
	//! Do Noting
}

void JsonSaveLoader::saveString(const char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();
	HANDLE file;
	// Byte Order Mark: 바이트 순서 표식
	WORD BOM = 0xFEFF;
	DWORD dwBytes = 0;
	DWORD dwRead;

	file = CreateFile
	(
		fileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// INVALID_HANDLE_VALUE: 초기화를 위해 사용되며 값은 보통 -1
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
	}
	else
	{
		WriteFile(file, buf, static_cast<DWORD>(strlen(buf) * sizeof(TCHAR)), &dwRead, NULL);
		CloseHandle(file);
	}
}

string JsonSaveLoader::loadString(const char* fileName)
{
	TCHAR buf[8193];
	ZeroMemory(buf, sizeof(buf));

	HANDLE file;
	DWORD dwBytes;

	file = CreateFile
	(
		fileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
		return "";
	}
	else
	{
		ReadFile(file, buf, 8192, &dwBytes, NULL);
		CloseHandle(file);
	}

	return string(buf);
}

void JsonSaveLoader::saveStringWithFileStream(const char* fileName, string data)
{
	ofstream outFile(fileName);

	outFile << data << endl;

	outFile.close();
}

string JsonSaveLoader::loadStringWithFileStream(string fileName)
{
	ifstream fileIn;

	/*
	ios::in		파일을 읽기만 가능한 모드로 개방
	ios::out	파일을 쓰기만 가능한 모드로 개방
	ios::ate	파일 개방이 될때 파일의 끝으로 파일 포인터 이동
	ios::binary	바이너리 모드로 개방
	ios::app	데이터를 맨 끝에서 부터 추가
	*/
	fileIn.open(fileName, ios::in);

	char data;
	string jsonStr;

	while (fileIn.get(data))
	{
		jsonStr += data;
	}

	fileIn.close();

	return jsonStr;
}

void JsonSaveLoader::saveJsonFile(const char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);

	saveStringWithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(string fileName)
{
	ifstream json_file(fileName, ifstream::binary);

	Json::Value root;
	json_file >> root;

	if (root == "")
	{
		LOG::e((string)fileName + " json 파일 생성 에러");
		return NULL;
	}

	json_file.close();

	return root;
}

