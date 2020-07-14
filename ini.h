#pragma once

class ini
{
public:
	ini();
	~ini();

	CString m_strIniPathFileName;
	DWORD m_lRetValue;

	CString GetStrValue(CString strSection, CString strKey, CString strDefault);
	void SetStrValue(CString strSection, CString strKey, CString strValue);
	int GetIntValue(CString strSection, CString strKey, int nDefault);
	void SetIntValue(CString strSection, CString strKey, int nValue);
};

