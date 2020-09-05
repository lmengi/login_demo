#include "stdafx.h"
#include "util.h"

std::wstring Utf82Str( const string& str )
{
	// utf8 --> unicode
	int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), str.length(), NULL, 0);
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), str.length(), wszString, wcsLen);
	wszString[wcsLen] = '\0';

	wstring str1 = wszString;
	delete wszString;

	return str1;
}

std::string Str2Utf8( const wstring& str )
{
	int utfLen = WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), wcslen(str.c_str()), NULL, 0, NULL, NULL);
	char* szString = new char[utfLen+1];

	WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), wcslen(str.c_str()), szString, utfLen, NULL, NULL);
	szString[utfLen] = '\0';

	string str1 = szString;
	delete szString;

	return str1;
}

vector<wstring> SplitString( wstring strData, size_t nSize, wstring strSpe )
{
	vector<wstring> result;

	int iTmpLen		= 0;
	while(iTmpLen < nSize)
	{
		int	iPos = strData.find(strSpe, iTmpLen);

		if (iPos == -1)
			break;

		wstring tmpStr = strData.substr(iTmpLen, iPos - iTmpLen);
		iTmpLen = iPos+strSpe.length();
		result.push_back(tmpStr);
	}

	if (iTmpLen < nSize)
		result.push_back(strData.substr(iTmpLen, nSize - iTmpLen));

	return result;
}

