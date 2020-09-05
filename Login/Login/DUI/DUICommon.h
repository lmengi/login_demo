#pragma once

#include "../../DuiLib/UIlib.h"


#ifndef NO_USING_DUILIB_NAMESPACE
using namespace DuiLib;
using namespace std;
#endif


#define UIBEGIN_MSG_MAP virtual void Notify(TNotifyUI& msg) { 
#define SUPER_HANDLER_MSG __super::Notify(msg);

//#define EVENT_HANDLER(event, func) if(msg) \
//{ \
//	func(msg);\
//	OutputDebugString(msg.sType + _T("\t\t") + msg.pSender->GetName() + _T("\r\n"));\
//}

#define EVENT_HANDLER(event, func) if( msg.sType == event && msg.pSender) \
{ \
	OutputDebugString(msg.sType + _T("\t\t") + msg.pSender->GetName() + _T("\r\n"));\
	func(msg);\
}

#define EVENT_ID_HANDLER(event, id, func) if(msg.sType == event && msg.pSender && _tcsicmp(msg.pSender->GetName(), id) == 0 ) \
{ \
	OutputDebugString(msg.sType + _T("\t\t") + msg.pSender->GetName() + _T("\r\n"));\
	func(msg);\
}

#define EVENT_ITEM_HANDLER_WITH_LIST_ID(event, id, func) if(msg.sType == event && msg.pSender && _tcsicmp(msg.pSender->GetParent()->GetParent()->GetName(), id) == 0 ) \
{ \
	OutputDebugString(msg.sType + _T("\t\t") + msg.pSender->GetParent()->GetParent()->GetName() + _T("\r\n"));\
	func(msg);\
}

#ifdef  _DEBUG
#define EVENT_PRINTER { \
	if(msg.pSender){\
		OutputDebugString(msg.sType + _T("\t\t") + msg.pSender->GetName() + _T("\r\n"));\
	}\
}
#else
#define EVENT_PRINTER
#endif



#define EVENT_BUTTON_CLICK(id,	func)		EVENT_ID_HANDLER(DUI_MSGTYPE_CLICK,			id, func)
#define EVENT_ITEM_CLICK(id,	func)		EVENT_ID_HANDLER(DUI_MSGTYPE_ITEMCLICK,		id, func)
#define EVENT_ITEM_RCLICK(id,	func)		EVENT_ID_HANDLER(DUI_MSGTYPE_ITEMRCLICK,	id, func)
#define EVENT_ITEM_LDBCLICK(id, func)		EVENT_ID_HANDLER(DUI_MSGTYPE_ITEMACTIVATE,	id, func)
#define EVENT_ITEM_SELECT(id,	func)		EVENT_ID_HANDLER(DUI_MSGTYPE_ITEMSELECT,	id, func)

#define UIEND_MSG_MAP return;} 


#define VERIFY_LPSZ(lpszVal, ret)  do { if ( (NULL == (lpszVal)) || (NULL == lpszVal[0]) ) return ret; } while ( 0 );
#define VERIFY_LPSZ_NOT_RET(lpszVal)  do { if ( (NULL == (lpszVal)) || (NULL == lpszVal[0]) ) return; } while ( 0 );
#define VERIFY_PTR(lpszVal, ret)  do { if ( (NULL == (lpszVal)) ) return ret; } while ( 0 );
#define VERIFY_PTR_NOT_RET(lpszVal)  do { if ( (NULL == (lpszVal)) ) return; } while ( 0 );


typedef enum
{
	UIFONT_GDI = 0,    /**< GDI */
	UIFONT_GDIPLUS,    /**< GDI+ */
	UIFONT_FREETYPE,   /**< FreeType */ 
	UIFONT_DEFAULT,    
} UITYPE_FONT;

#define DT_CALC_SINGLELINE		 DT_SINGLELINE| DT_LEFT_EX|DT_NOPREFIX  //计算单行
#define DT_CALC_MULTILINE		 DT_WORDBREAK | DT_EDITCONTROL | DT_LEFT_EX | DT_NOPREFIX // 计算多行