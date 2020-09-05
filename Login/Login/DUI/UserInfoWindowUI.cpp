//#include "stdafx.h"
#include "UserInfoWindowUI.h"
#include "../resource.h"
#include "../login/LoginDll.h"
#include "../json/json.h"

CUserInfoWindowUI::CUserInfoWindowUI()
{
}

CUserInfoWindowUI::~CUserInfoWindowUI()
{

}

LPCTSTR CUserInfoWindowUI::GetWindowClassName() const
{
	return _T("CUserInfoWindowUI");
}

CDuiString CUserInfoWindowUI::GetSkinFile()
{
   return _T("LoginWindow\\UserInfoWindowUI.xml");
}

CDuiString CUserInfoWindowUI::GetSkinFolder()
{
   return _T("skin");
}

void CUserInfoWindowUI::InitWindow()
{
	m_userNameEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("UserName")));
	m_userNumEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("UserNumber")));
	m_nickNameEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("Nickname")));
	m_orgIdEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("OrganizationID")));
	m_orgNameEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("OrganizationName")));
}


//关闭按钮事件响应
void CUserInfoWindowUI::OnBtnCloseClick(TNotifyUI& msg)
{
	//::PostMessage(this->GetHWND(), WM_CLOSE, 0, 0);
	TerminateProcess(GetCurrentProcess(),0);
}

//最小化按钮事件响应
void CUserInfoWindowUI::OnBtnMinClick(TNotifyUI& msg)
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
}

void CUserInfoWindowUI::ShowUI()
{
	Create(NULL,_T("个人资料"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	CenterWindow();
	ShowWindow(true);

	//设置窗口图标
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	if (NULL == hInstance)
	{
		return;
	}
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	if (NULL == hIcon)
	{
		return;
	}

	// 设置窗口的大小图标 
	::SendMessage(CUserInfoWindowUI::GetInstance()->GetHWND(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}


bool CUserInfoWindowUI::GetUserInfoCallBack(void* pObj)
{
	tagContext* ptagContext = (tagContext*)pObj;
	CUserInfoWindowUI* pPersonalInfoWindow = (CUserInfoWindowUI*)ptagContext->pUserData;
	if (ptagContext->dwErrorCode == 0)
	{
		string strPersonalInfo = ptagContext->pData;

		Json::Reader reader;
		Json::Value root;

		bool res = reader.parse(strPersonalInfo.c_str(), root);
		if( res && root.isArray() && root.size() == 1 )
		{
			int i = 0;
			Json::Value value = root[i];
			string strUserId;
			string strUsername;
			string strNickname;
			string strCoverageId;
			string strCoverageName;
			JsonUtf8StringAssign(strUserId, value["id"]);
			JsonUtf8StringAssign(strUsername, value["username"]);
			JsonUtf8StringAssign(strNickname, value["nickname"]);
			JsonUtf8StringAssign(strCoverageId, value["coverageid"]);
			JsonUtf8StringAssign(strCoverageName, value["coveragename"]);

			pPersonalInfoWindow->SetUserInfo(strUserId, strUsername, strNickname, strCoverageId, strCoverageName);
		}
	}else
	{
		OutputDebugString(_T("获取用户详情失败!"));
	}
	return true;
}

void CUserInfoWindowUI::GetUserInfo(string strUserId)
{
	GetUserProfile(strUserId.c_str(), &CUserInfoWindowUI::GetUserInfoCallBack, this);
}

void CUserInfoWindowUI::SetUserInfo(string strUserId, string strUsername, string strNickname, string strCoverageId, string strCoverageName)
{
	if (m_userNumEdit)
		m_userNumEdit->SetText(strUserId.c_str());
	if (m_userNameEdit)
		m_userNameEdit->SetText(strUsername.c_str());
	if (m_nickNameEdit)
		m_nickNameEdit->SetText(strNickname.c_str());
	if (m_orgIdEdit)
		m_orgIdEdit->SetText(strCoverageId.c_str());
	if (m_orgNameEdit)
		m_orgNameEdit->SetText(strCoverageName.c_str());
}