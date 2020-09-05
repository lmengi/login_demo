#pragma once

class CUser 
{
	enum{LOGIN_OK, LOGIN_PARAM_ERROR, LOGIN_FAILED};
	enum{GET_USERPROFILE_OK, GET_USERPROFILE_PARAM_ERROR, GET_USERPROFILE_FAILED};
public:
	CUser();
	~CUser();

	int Login(string strLoginJson, string& strOutJson);
	int GetUserProfile(string strUserId, string& strOutJson);
};