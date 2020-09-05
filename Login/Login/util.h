#pragma once

wstring		Utf82Str(const string& str);
string		Str2Utf8(const wstring& str);

#define ImplementInstance(cls)\
public:\
	static cls*	cls::GetInstance(){\
	static cls* m_pInstance = NULL;\
	if(!m_pInstance){\
	m_pInstance = new cls;\
	}\
	return m_pInstance;\
}


#define JsonUtf8StringAssign(strDest, jsValue){\
	if (!jsValue.isNull()\
	&& jsValue.isString()){\
	strDest = jsValue.asString();\
}\
}

#define JsonUtf8StringAppend(strDest, jsValue){\
	if (!jsValue.isNull()\
	&& jsValue.isString()){\
	strDest += jsValue.asString();\
}\
}

#define JsonUtf8StringToString(strDest, jsValue){\
	if (!jsValue.isNull()\
	&& jsValue.isObject()){\
	strDest += jsValue.toStyledString();\
}\
}

#define JsonIntAssign(nDest, jsValue){\
	if (!jsValue.isNull()\
	&& jsValue.isInt()){\
	nDest =jsValue.asInt();\
}\
}

#define JsonIntegerAssign(nDest, jsValue){\
	if (jsValue.isInt()){\
	nDest =jsValue.asInt();\
	}\
	else if (jsValue.isString()){\
	nDest = atoi(jsValue.asCString());\
}\
}

#define JsonBoolAssign(bDest, jsValue){\
	if (jsValue.isBool()){\
	bDest = jsValue.asBool();\
	}\
}

#define JsonDoubleAssign(bDest, jsValue){\
	if (!jsValue.isNull()\
	&& jsValue.isDouble()){\
	bDest = jsValue.asDouble();\
}\
}

vector<wstring> SplitString( wstring strData, size_t nSize, wstring strSpe );