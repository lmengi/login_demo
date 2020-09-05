// PPTShellSetup.cpp : Defines the entry point for the application.
//



#include "stdafx.h"
#include "Login.h"
#include "DUI/LoginWindowUI.h"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return 0;
	}

	 HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));


	CLoginWindowUI* pLoginWindowUI = new CLoginWindowUI();
	pLoginWindowUI->ShowUI();

	//ÉèÖÃ´°¿ÚÍ¼±ê
	if (hIcon)
	{
		::SendMessage(pLoginWindowUI->GetHWND(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	}


	CPaintManagerUI::MessageLoop();
	delete pLoginWindowUI;

	::CoUninitialize();
	return 0;
}