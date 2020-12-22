#include <Windows.h>
#include <iostream>

using namespace std;

#define TESTCOUNT 2

DWORD WINAPI AffinityThread(LPVOID IpParam){
    DWORD TID = 0;
    TID = (DWORD)IpParam;

    SetThreadAffinityMask(GetCurrentThread(), 1 << 2);
    for(int index = 0; index < TESTCOUNT; index++)
        cout << "Thread ID : " << TID << " Processor : " << GetCurrentProcessorNumber() << endl; 

    return 0;
}

DWORD WINAPI Thread(LPVOID IpParam){
    DWORD TID = 0;
    TID = (DWORD)IpParam;
   for(int index = 0; index < TESTCOUNT; index++)
        cout << "Thread ID : " << TID << " Processor : " << GetCurrentProcessorNumber() << endl; 
   
    return 0;
}

int main(void){
    
    HANDLE hThread[TESTCOUNT] = {0, };
    HANDLE hThreadMask[TESTCOUNT] = {0, };

    for(int index = 0; index < TESTCOUNT; index++)
        hThread[index] = CreateThread(NULL, 0, Thread, (LPVOID)index, 0, NULL);

    WaitForMultipleObjects(TESTCOUNT, hThread, TRUE, INFINITE);

    cout << "Set Thread Affinity" << endl;

    for(int index = 0; index < TESTCOUNT; index++)
        hThreadMask[index] = CreateThread(NULL, 0, AffinityThread, (LPVOID)index, 0, NULL);

    WaitForMultipleObjects(TESTCOUNT, hThreadMask, TRUE, INFINITE);

    for(int index = 0; index < TESTCOUNT; index++){
        CloseHandle(hThread[index]);
        CloseHandle(hThreadAffinity[index]);
    }
    
    return 0;
}