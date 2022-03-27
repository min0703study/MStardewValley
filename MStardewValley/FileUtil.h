#pragma once
/*
	MAP 파일 로드
*/
template<typename T>
inline bool LoadFile(char* fileName, T& saveFile, DWORD readSize) {
	HANDLE  hFile;
	DWORD  dwRead = 0;

	hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(hFile, saveFile, readSize, &dwRead, NULL);
	CloseHandle(hFile);

	return dwRead == 0;
};

/*
	MAP 파일 저장
*/
template<typename T>
inline bool SaveFile(char* fileName, T& saveFile, DWORD writeSize) {
	HANDLE  hFile;
	DWORD  dwRead = 0;

	hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, saveFile, writeSize, &dwRead, NULL);
	CloseHandle(hFile);

	return dwRead == 0;
};

inline Json::Value LoadJsonFile(char* fileName)
{
	ifstream json_file(fileName, ifstream::binary);

	Json::Value root;
	json_file >> root;
	json_file.close();

	return root;
};

