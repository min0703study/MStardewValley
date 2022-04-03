#pragma once
/*
	MAP ���� �ε�
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
	MAP ���� ����
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
