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
	// Byte Order Mark: ����Ʈ ���� ǥ��
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

	// INVALID_HANDLE_VALUE: �ʱ�ȭ�� ���� ���Ǹ� ���� ���� -1
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
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
		MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
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
	ios::in		������ �б⸸ ������ ���� ����
	ios::out	������ ���⸸ ������ ���� ����
	ios::ate	���� ������ �ɶ� ������ ������ ���� ������ �̵�
	ios::binary	���̳ʸ� ���� ����
	ios::app	�����͸� �� ������ ���� �߰�
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
		LOG::e((string)fileName + " json ���� ���� ����");
		return NULL;
	}

	json_file.close();

	return root;
}

