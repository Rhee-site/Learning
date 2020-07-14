#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include <iostream>

using namespace std;

#define DATA_LEN 1024

typedef struct {
	char chData[DATA_LEN];
	int nData;
}MMFTEST;

int main(void){
  HANDLE hReadMap = NULL;
	MMFTEST* m_Data;
	int m_nData;
	char m_chData[DATA_LEN];
	char chNo;
	bool bEnd = false;

	while (true) {
		cout << "1. Write Memory" << endl;
		cout << "2. Read Memory" << endl;
		cout << "0. Exit" << endl;

		chNo = _getch();

		switch (chNo)
		{
		case 49:
			break;
		case 50:
			hReadMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MemoryMapTest");

			if (hReadMap == NULL)
				cout << "Open File Map Fail " << endl;

			if (GetLastError() == ERROR_ALREADY_EXISTS)
				cout << "File Map Exists" << endl;

			m_Data = (MMFTEST*)MapViewOfFile(hReadMap, FILE_MAP_READ, 0, 0, 0);
			m_nData = m_Data->nData;
			strcpy(m_chData, m_Data->chData);

			cout << "int Data : " << m_nData << endl;
			cout << "char Data : " << m_chData << endl;

			if (CloseHandle(hReadMap))
				cout << "Handle close success" << endl;
			else
				cout << "Handle close fail" << endl;

			break;
		case 48:
			bEnd = true;
			break;
		default:
			cout << "Wrong Input" << endl;
			break;
		}

		if (bEnd)
			break;
	}

  return 0;
}