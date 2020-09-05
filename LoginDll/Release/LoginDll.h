#ifndef _LOGININTERFACE_H_
#define _LOGININTERFACE_H_

#ifdef LOGININTERFACE_EXPORTS
#define EXPORT_API extern "C" __declspec(dllexport)
#else
#define EXPORT_API extern "C" __declspec(dllimport)
#endif

typedef struct _tagContext
{
	DWORD dwErrorCode;
	char* pData;
	void* pUserData;
}tagContext;

EXPORT_API void Login(LPCSTR szLoginJson, void* pCallBack, void* pUserData);
EXPORT_API void GetUserProfile(LPCSTR szUserId, void* pCallBack, void* pUserData);

#endif



