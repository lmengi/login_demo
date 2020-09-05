#ifndef CLOGINWINDOWUI_H
#define CLOGINWINDOWUI_H

#include <objbase.h>
#include "DUICommon.h"

/*登录窗口类*/
class CLoginWindowUI : public WindowImplBase
{
public:
    CLoginWindowUI();
    virtual ~CLoginWindowUI();

	UIBEGIN_MSG_MAP
	EVENT_BUTTON_CLICK(_T("minbtn"),OnBtnMinClick);
	EVENT_BUTTON_CLICK(_T("closebtn"),OnBtnCloseClick);
	EVENT_BUTTON_CLICK(_T("loginBtn"),OnBtnLoginClick);
	EVENT_BUTTON_CLICK(_T("cancelBtn"),OnBtnCancelClick);
	UIEND_MSG_MAP

private:
	//登录按钮事件响应
	void OnBtnLoginClick(TNotifyUI& msg);
	//关闭按钮事件响应
	void OnBtnCloseClick(TNotifyUI& msg);
	//最小化按钮事件响应
	void OnBtnMinClick(TNotifyUI& msg);
	//取消按钮事件响应
	void OnBtnCancelClick(TNotifyUI& msg);


public:
	//创建窗口
	void ShowUI();

protected:
    virtual LPCTSTR GetWindowClassName() const;
    virtual CDuiString GetSkinFile();
    virtual void InitWindow();
    virtual CDuiString GetSkinFolder();
   // void Notify(TNotifyUI& msg);

	virtual LRESULT		HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/*登录回调函数*/
	static bool LoginCallBack(void* pObj);

	/*显示登录结果提示*/
	void ShowLoginTip(string strTip);

	/*显示个人资料窗口*/
	void ShowUserInfoWindow(string strUserId);

	/*设置用户ID*/
	void SetUserId(string strUserId);
private:

	CEditUI*   m_userNameEdit;
	CEditUI*   m_passWordEdit;

	CVerticalLayoutUI*	m_pLoginLayout;
	CVerticalLayoutUI*	m_pLoginTipLayout;

	string	   m_strUserId;
};
#endif // CLOGINWINDOW_H
