#include "stdafx.h"
#include "DataBaseOperation.h"
#include "Util.h"

#pragma comment(lib, "sqlite3.lib")

CDataBaseOperateion::CDataBaseOperateion( void )
{
	m_pSqlite3 = NULL;
}

CDataBaseOperateion::~CDataBaseOperateion( void )
{
	if(m_pSqlite3)
		DataBaseClose();
}

bool CDataBaseOperateion::DataBaseOpen()
{
	TCHAR szDir[MAX_PATH];
	GetModuleFileName(NULL, szDir, MAX_PATH);

	TCHAR* p = _tcsrchr(szDir, _T('\\'));
	*(p + 1) = '\0';

	wstring wstrDBPath = szDir;
	wstrDBPath += L"Login.db3";

	bool bRet = false;
	int nRet = sqlite3_open16(wstrDBPath.c_str(), &m_pSqlite3);
	if (nRet == SQLITE_OK)  
	{  
		bRet = true;
	}  

	return bRet;
}

bool CDataBaseOperateion::DataBaseInsert( string& strSQLJson )
{
	bool bRet = false;
	if(m_pSqlite3 == NULL)
		DataBaseOpen();
	if(m_pSqlite3)
	{
		char* szErrMsg;  
		int nRes = sqlite3_exec(m_pSqlite3 , strSQLJson.c_str() ,0 ,0, &szErrMsg);  
		if (nRes == SQLITE_OK)    
		{  
			bRet = true;
		}  
	}
	
	return bRet;
}

bool CDataBaseOperateion::DataBaseFind( string& strInSQLJson, string& strOutSQLJson )
{
	bool bRet = false;
	char** pszResult;
	char* szErrMsg;
	int nRow;
	int nCol;
	if(m_pSqlite3 == NULL)
		DataBaseOpen();
	if(m_pSqlite3)
	{
		int nRes = sqlite3_get_table(m_pSqlite3, strInSQLJson.c_str(), &pszResult, &nRow, &nCol, &szErrMsg);  
		if (nRes == SQLITE_OK)    
		{  
			bRet = true;
			if(nRow > 0)
			{
				Json::Value root;
				Json::FastWriter writer;
				int nIndex = nCol;
				for(int i = 0; i < nRow ; i++)
				{
					Json::Value value;
					for(int j = 0; j < nCol; j++)
					{
						value[pszResult[j]] = pszResult[nIndex];				
						++nIndex;
					}
					root.append(value);
				}
				//			root["Count"] = nIndex;
				sqlite3_free_table(pszResult);
				strOutSQLJson = writer.write(root);
			}
		}  
	}
	 
	return bRet;
}

bool CDataBaseOperateion::DataBaseClose()
{
	int nRes = sqlite3_close(m_pSqlite3);
	if (nRes == SQLITE_OK)    
	{  
		m_pSqlite3 = NULL;
	}
	
	return true;
}
