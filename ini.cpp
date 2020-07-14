#include "ini.h"

ini::ini()
{
}

ini::~ini()
{
}

CString ini::GetStrValue(CString strSection, CString strKey, CString strDefault)
{
	WCHAR ac_Result[255];
	m_lRetValue = GetPrivateProfileString(strSection, strKey,
		strDefault, ac_Result, 255, m_strIniPathFileName);

	CString strResult(ac_Result);
	return strResult;
}

void ini::SetStrValue(CString strSection, CString strKey, CString strValue)
{
	WritePrivateProfileString(strSection, strKey,
		strValue, m_strIniPathFileName);
}

int ini::GetIntValue(CString strSection, CString strKey, int nDefault)
{
	CString strDefault = _T("");
	CString strReturn = _T("");
	int nReturn = 0;

	strDefault.Format(_T("%d"), nDefault);
	strReturn = GetStrValue(strSection, strKey, strDefault);
	nReturn = _wtoi(strReturn);

	return nReturn;
}

void ini::SetIntValue(CString strSection, CString strKey, int nValue)
{
	CString strValue = _T("");
	strValue.Format(_T("%d"), nValue);
	SetStrValue(strSection, strKey, strValue);
}
