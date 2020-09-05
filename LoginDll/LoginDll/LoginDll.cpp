// LoginInterface.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LoginDll.h"
#include "User.h"

typedef bool ( __cdecl * lpCallBack )( void* pObj);

lpCallBack				pCallBack			= NULL;

typedef struct _tagThreadParam
{
	char* pszBuff;
	void* pCallBack;
	void* pUserData;
}tagThreadParam;

static DWORD WINAPI LoginThread(LPARAM lParam)
{
	tagThreadParam* pThreadParam = (tagThreadParam*)lParam;

	string strOutJson;
	CUser User;
	int nRet = User.Login(pThreadParam->pszBuff, strOutJson);

	tagContext context ;
	context.pUserData = pThreadParam->pUserData;
	context.dwErrorCode = nRet;
	context.pData = (char *)strOutJson.c_str();

	pCallBack = (lpCallBack)pThreadParam->pCallBack;
	pCallBack(&context);

	delete pThreadParam->pszBuff;
	delete pThreadParam;
	return 0;
}

static DWORD WINAPI GetUserProfileThread(LPARAM lParam)
{
	tagThreadParam* pThreadParam = (tagThreadParam*)lParam;

	string strOutJson;
	CUser User;
	int nRet = User.GetUserProfile(pThreadParam->pszBuff, strOutJson);
	
	tagContext context = {0};
	context.pUserData = pThreadParam->pUserData;
	context.dwErrorCode = nRet;
	context.pData = (char *)strOutJson.c_str();

	pCallBack = (lpCallBack)pThreadParam->pCallBack;
	pCallBack(&context);

	delete pThreadParam->pszBuff;
	delete pThreadParam;
	return 0;
}

void Login( LPCSTR szLoginJson, void* pCallBack, void* pUserData )
{
	tagThreadParam* pThreadParam  = new tagThreadParam;
	pThreadParam->pCallBack = pCallBack;
	pThreadParam->pUserData = pUserData;
	int nLen = strlen(szLoginJson);
	char * p = new char[nLen + 1];
	p[nLen] = 0;
	strcpy(p, szLoginJson);
	pThreadParam->pszBuff = p;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoginThread, pThreadParam, 0, NULL);
}

void GetUserProfile( LPCSTR szUserId, void* pCallBack, void* pUserData )
{
	tagThreadParam* pThreadParam  = new tagThreadParam;
	pThreadParam->pCallBack = pCallBack;
	pThreadParam->pUserData = pUserData;
	int nLen = strlen(szUserId);
	char * p = new char[nLen + 1];
	p[nLen] = 0;
	strcpy(p, szUserId);
	pThreadParam->pszBuff = p;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetUserProfileThread, pThreadParam, 0, NULL);
}
