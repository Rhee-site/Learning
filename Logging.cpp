#include <iostream>
#include <assert.h>

using namespace std;

class Log {
private:
    int m_nerrNum;
    const char* m_chfuncName;
    int m_nlineNum;
public:
    Log(int errNum, const char* funcName, int lineNum) {
        m_nerrNum = errNum;
        m_chfuncName = funcName;
        m_nlineNum = lineNum;
    }
    ~Log() {};
    void Logging() {
        cout << "Logging " << __DATE__ << " " << __TIME__ << endl;
        cout << "Function Name : " << m_chfuncName << endl;
        cout << "Line : " << m_nlineNum << endl;
        cout << "Context : " << m_nerrNum << endl;
    }
};

void Set(int nValue) {
    
    if (nValue < 0) throw Log(nValue, __func__, __LINE__);

    cout << "Set Value : " << nValue << endl;
}

int main(void) {

    int nValue = -100;

    try {
        Set(nValue);
    }
    catch (Log & e) {
        e.Logging();
    }

    return 0;
}