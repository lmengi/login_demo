#pragma once
#include "Util.h"
#include "sqlite/sqlite3.h"

class CDataBaseOperateion
{
public:
	CDataBaseOperateion(void);
	~CDataBaseOperateion(void);
public:
	bool DataBaseOpen();
	bool DataBaseInsert(string& strSQLJson);
	bool DataBaseFind( string& strInSQLJson, string& strOutSQLJson );
	bool DataBaseClose();

	ImplementInstance(CDataBaseOperateion);
private:
	sqlite3* m_pSqlite3;
};
