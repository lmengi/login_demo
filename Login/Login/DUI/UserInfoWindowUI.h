#ifndef CUSERINFOWINDOWUI_H
#define CUSERINFOWINDOWUI_H

#include <objbase.h>
#include "DUICommon.h"
#include "../util.h"

class CUserInfoWindowUI : public WindowImplBase
{
public:
    CUserInfoWindowUI();
    virtual ~CUserInfoWindowUI();

	UIBEGIN_MSG_MAP
		EVENT_BUTTON_CLICK(_T("minbtn"),OnBtnMinClick);
	EVENT_BUTTON_CLICK(_T("closebtn"),OnBtnCloseClick);
	UIEND_MSG_MAP
private:
	//关闭按钮事件响应
	void OnBtnCloseClick(TNotifyUI& msg);
	//最小化按钮事件响应
	void OnBtnMinClick(TNotifyUI& msg);
public:

	//获取用户详情
	void GetUserInfo(string strUserId);

	void SetUserInfo(string strUserId, string strUsername, string strNickname, string strCoverageId, string strCoverageName);

	//创建窗口函数
	void ShowUI();

	ImplementInstance(CUserInfoWindowUI);

protected:
    virtual LPCTSTR GetWindowClassName() const;
    virtual CDuiString GetSkinFile();
    virtual void InitWindow();
    virtual CDuiString GetSkinFolder();

	/*获取个人资料*/
	static bool GetUserInfoCallBack(void* pObj);

private:
	CEditUI*   m_userNumEdit;
	CEditUI*   m_userNameEdit;
	CEditUI*   m_nickNameEdit;
	CEditUI*   m_orgIdEdit;
	CEditUI*   m_orgNameEdit;

	string     m_strUserId;
};
#endif // CPERSONALINFOWINDOW_H
