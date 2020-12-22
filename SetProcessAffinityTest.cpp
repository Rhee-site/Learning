#include <Windows.h>
#include <iostream>

using namespace std;

#define TESTCOUNT 10

int main(void){
    
    for(int index = 0; index < TESTCOUNT; index++)
        cout << "Processor : " << GetCurrentProcessorNumber() << endl;

    cout << "Set Processor Affinity" << endl;

    SetProcessAffinityMask(GetCurrentProcess(), 1 << 2);

    for(int index = 0; index < TESTCOUNT; index++)
        cout << "Processor : " << GetCurrentProcessorNumber() << endl;
    
    return 0;
}