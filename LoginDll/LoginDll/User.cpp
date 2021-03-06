#include "stdafx.h"
#include "User.h"
#include "DataBaseOperation.h"

CUser::CUser()
{

}

CUser::~CUser()
{

}

int CUser::Login(string strLoginJson, string& strOutJson)
{
	int nRet = LOGIN_OK;
	Json::Value root;
	Json::Reader reader;

	bool res = reader.parse(strLoginJson.c_str(), root);
	if( res )
	{
		if( root.isObject() )
		{
			string strUserName;
			string strPassword;
			string strCoverageName;
			JsonUtf8StringAssign(strUserName, root["username"]);
			JsonUtf8StringAssign(strPassword, root["password"]);
			JsonUtf8StringAssign(strCoverageName, root["coveragename"]);
			
			string strSQL = "select * from User,Coverage WHERE username='";
			strSQL += strUserName;
			strSQL += "' AND password='";
			strSQL += strPassword;
			strSQL += "' And User.coverageid = Coverage.coverageid And Coverage.coveragename ='";
			strSQL += strCoverageName;
			strSQL += "'";

			bool bRet = CDataBaseOperateion::GetInstance()->DataBaseFind(strSQL, strOutJson);
			if(!bRet)
			{
				nRet = LOGIN_FAILED;
			}
			else
			{
				if(strOutJson.empty())
					nRet = LOGIN_FAILED;
			}
		}
		else
		{
			nRet = LOGIN_PARAM_ERROR;
		}
	}
	else
	{
		nRet = LOGIN_PARAM_ERROR;
	}

	return nRet;
}

int CUser::GetUserProfile(string strUserId, string& strOutJson)
{
	int nRet = GET_USERPROFILE_OK;

	if(!strUserId.empty())
	{
		string strSQL = "select User.id, User.username, UserProfile.nickname, Coverage.coverageid, Coverage.coveragename from User, UserProfile, Coverage where User.id = ";
		strSQL += strUserId;
		strSQL += " and User.coverageid = Coverage.coverageid and User.id = NDUserProfile.userid";

		bool bRet = CDataBaseOperateion::GetInstance()->DataBaseFind(strSQL, strOutJson);
		if(!bRet)
			nRet = GET_USERPROFILE_FAILED;
		else
		{
			if(strOutJson.empty())
				nRet = GET_USERPROFILE_FAILED;
		}
	}
	else
	{
		nRet = GET_USERPROFILE_PARAM_ERROR;
	}

	return nRet;
}
