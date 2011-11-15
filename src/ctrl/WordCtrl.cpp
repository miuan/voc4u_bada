/*
 * WordCtrl.cpp
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#include "WordCtrl.h"

WordCtrl * WordCtrl::__wc = null;

WordCtrl::WordCtrl() :
	__db(null)
{
}

WordCtrl::~WordCtrl()
{
	if (__db)
		delete __db;
}

WordCtrl * WordCtrl::GetInstance()
{
	if (!__wc)
	{
		__wc = new WordCtrl();
		__wc->Init();
	}

	return __wc;
}

bool WordCtrl::GetLessonEnabled(const int lesson)
{
	result r;

	String sql;
	sql.Format(1000, LESSON_EXISTS, TABLE_NAME, COLUMN_LESSON, lesson);

	AppLogDebug("SQL: (%S)", sql.GetPointer());
	DbEnumerator* pEnum = __db->QueryN(sql);

	int count = 0;
	if (pEnum)
	{
		while (pEnum->MoveNext() == E_SUCCESS)
		{
			pEnum->GetIntAt(0, count);
			break;
		}

		delete pEnum;
	}
	return count > 0;
}

result WordCtrl::PrepareDB()
{
	result r;
	String sql;
	sql.Format(1000, INSERT_TABLE, TABLE_NAME, COLUMN_ID, COLUMN_LESSON, COLUMN_LERN, COLUMN_NATIVE, COLUMN_LWEIGHT, COLUMN_NWEIGHT, COLUMN_USER_CHANGE);

	AppLogDebug("SQL: (%ls)", sql.GetPointer());
	r = __db->ExecuteSql(sql, true);

	if (IsFailed(r))
	{
		AppLog("DB not initialized (%1s)", GetErrorMessage(r));
		return r;
	}

	return r;
}

result WordCtrl::Init()
{
	result r = E_SUCCESS;
	__db = new Database();

	if (!Database::Exists(DB_NAME))
	{
		__db->Construct(DB_NAME, true);
		r = PrepareDB();
	}
	else __db->Construct(DB_NAME, false);

	return r;
}

bool WordCtrl::AddWord(Word &word)
{
	return true;
}
