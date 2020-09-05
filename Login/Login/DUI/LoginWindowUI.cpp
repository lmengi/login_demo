//#include "stdafx.h"
#include "LoginWindowUI.h"
#include "../resource.h"
#include "UserInfoWindowUI.h"
#include "../json/json.h"
#include "../md5.h"
#include "../login/LoginDll.h"
#include "../util.h"

#define SHOW_PERSONAL_WND WM_USER+110

#pragma comment(lib,"login/LoginDll.lib")

CLoginWindowUI::CLoginWindowUI()
{
	m_pLoginLayout = NULL;
	m_pLoginTipLayout = NULL;
}

CLoginWindowUI::~CLoginWindowUI()
{

}

LPCTSTR CLoginWindowUI::GetWindowClassName() const
{
    return _T("CLoginWindowUI");
}

CDuiString CLoginWindowUI::GetSkinFile()
{
   return _T("LoginWindow\\LoginWindowUI.xml");
}

CDuiString CLoginWindowUI::GetSkinFolder()
{
   return _T("skin");
}

void CLoginWindowUI::InitWindow()
{
	m_userNameEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("Username")));
	m_passWordEdit = dynamic_cast<CEditUI*>(m_PaintManager.FindControl(_T("Password")));

	m_pLoginLayout = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("loginLayout")));
	m_pLoginTipLayout = static_cast<CVerticalLayoutUI *>(m_PaintManager.FindControl(_T("loginTipLayout")));

	if (m_userNameEdit)
		m_userNameEdit->SetText(_T("508816"));
	
	if (m_passWordEdit)
		m_passWordEdit->SetText(_T("123456"));
	
}


void CLoginWindowUI::ShowUI()
{
	Create(NULL,_T("网龙99游"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	CenterWindow();
	ShowWindow();
}

vector<string> SplitString( string strData, size_t nSize, string strSpe)
{
	vector<string> result;

	int iTmpLen		= 0;
	while(iTmpLen < nSize)
	{
		int	iPos = strData.find(strSpe, iTmpLen);

		if (iPos == -1)
			break;

		string tmpStr = strData.substr(iTmpLen, iPos - iTmpLen);
		iTmpLen = iPos+strSpe.length();
		result.push_back(tmpStr);
	}

	if (iTmpLen < nSize)
		result.push_back(strData.substr(iTmpLen, nSize - iTmpLen));

	return result;
}

//登录按钮事件响应
void CLoginWindowUI::OnBtnLoginClick(TNotifyUI& msg)
{
	m_pLoginLayout->SetVisible(false);
	m_pLoginTipLayout->SetVisible(true);

	string strUserName = m_userNameEdit->GetText();
	string strPassword = m_passWordEdit->GetText();
	MD5* mdTemp = new MD5(strPassword);

	string strTemp = mdTemp->md5();

	Json::Value root;

	root["password"] = Json::Value(strTemp.c_str());

	vector<string> vecParams = SplitString(strUserName, strUserName.length(), _T("@"));
	if(vecParams.size() == 2)
	{
		root["coveragename"] = Json::Value(vecParams[1].c_str());
		root["username"] = Json::Value(vecParams[0].c_str());
	}
	else
	{
		root["coveragename"] = _T("nd");
		root["username"] = Json::Value(strUserName.c_str());
	}

	delete mdTemp;

	string StrPostData = root.toStyledString();

	// 登录
	Login(StrPostData.c_str(), &CLoginWindowUI::LoginCallBack, this);
}

//关闭按钮事件响应
void CLoginWindowUI::OnBtnCloseClick(TNotifyUI& msg)
{
	//::PostMessage(this->GetHWND(), WM_CLOSE, 0, 0);
	TerminateProcess(GetCurrentProcess(),0);
}

//最小化按钮事件响应
void CLoginWindowUI::OnBtnMinClick(TNotifyUI& msg)
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
}

//取消按钮事件响应
void CLoginWindowUI::OnBtnCancelClick(TNotifyUI& msg)
{
	m_pLoginLayout->SetVisible(true);
	m_pLoginTipLayout->SetVisible(false);
}

LRESULT CLoginWindowUI::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if( uMsg == SHOW_PERSONAL_WND )
	{
		ShowUserInfoWindow(m_strUserId);
	}

	return 1;
}

//登录回调函数
bool CLoginWindowUI::LoginCallBack(void* pObj)
{
	tagContext* ptagContext = (tagContext*)pObj;
	CLoginWindowUI* pLoginWindow = (CLoginWindowUI*)ptagContext->pUserData;
	if (ptagContext->dwErrorCode == 0)
	{
		OutputDebugString(_T("登录成功!"));
		string strUseName = ptagContext->pData;

		Json::Reader reader;
		Json::Value root;

		bool res = reader.parse(strUseName.c_str(), root);
		if( res && root.isArray() && root.size() == 1 )
		{
			int i = 0;
			Json::Value value = root[i];
			string strUserId;
			JsonUtf8StringAssign(strUserId, value["id"]);
			pLoginWindow->SetUserId(strUserId);
			::SendMessage(pLoginWindow->GetHWND(), SHOW_PERSONAL_WND, NULL, NULL);
		}
	}
	else
	{
		OutputDebugString(_T("登录失败!"));
		pLoginWindow->ShowLoginTip(_T("登录失败!"));
	}

	return true;
}

void CLoginWindowUI::ShowLoginTip(string strTip)
{
	m_pLoginLayout->SetVisible(true);
	m_pLoginTipLayout->SetVisible(false);
	CLabelUI* pLabelLoginTip = static_cast<CLabelUI *>(m_PaintManager.FindControl(_T("loginTip")));
	if (pLabelLoginTip)
	{
		pLabelLoginTip->SetVisible(true);
		pLabelLoginTip->SetText(strTip.c_str());
	}
}

void CLoginWindowUI::ShowUserInfoWindow(string strUserId)
{
	ShowWindow(false);
	CUserInfoWindowUI* pUserInfoUI = CUserInfoWindowUI::GetInstance();
	pUserInfoUI->ShowUI();//展示窗口
	pUserInfoUI->GetUserInfo(strUserId);
}

void CLoginWindowUI::SetUserId(string strUserId)
{
	m_strUserId = strUserId;
}

