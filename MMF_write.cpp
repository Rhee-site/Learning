#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include <iostream>

using namespace std;

#define DATA_LEN 1024

typedef struct{
  char chData[DATA_LEN];
  int nData;
}MMFTEST;

int main(void){
  HANDLE hWriteMAp;
  MMFTEST* m_Data;
  int m_nData;
  char m_chData[DATA_LEN];
  char chNo;
  bool bEnd = false;
  
  hWriteMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(MMFTEST), L"MemoryMapTest");

	if (hWriteMap == NULL)
		cout << "Create File Map Fail" << endl;

	if (GetLastError() == ERROR_ALREADY_EXISTS)
		cout << "File Map Exists" << endl;
  
  while(true){
    cout << "1. Write Memory" << endl;
		cout << "2. Read Memory" << endl;
		cout << "0. Exit" << endl;

		chNo = _getch();

		switch (chNo)
		{
		case 49:
			m_Data = (MMFTEST*)MapViewOfFile(hWriteMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

			if (m_Data == NULL)
				cout << "Connect Virtual Memory Fail" << endl;

			cout << "Data Input Start" << endl;

			cout << "char Data input : ";
			cin >> m_chData;
			strcpy(m_Data->chData, m_chData);
			cout << "int Data input : ";
			cin >> m_nData;
			m_Data->nData = m_nData;

			cout << "Data Input Finsh" << endl;

			UnmapViewOfFile(m_Data);
			break;
		case 50:
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
  
  if (CloseHandle(hWriteMap))
		cout << "Handle close success" << endl;
	else
		cout << "Handle close fail" << endl;
  
  return 0;
}