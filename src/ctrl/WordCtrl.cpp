/*
 * WordCtrl.cpp
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#include "WordCtrl.h"

WordCtrl * WordCtrl::__wc = null;

WordCtrl::WordCtrl() :
	__db(null), __lw(null), __lwLissener(null)
{
}

WordCtrl::~WordCtrl()
{
	if (__lw)
	{
		__lw->SetLessonWorkerLissener(null);

		while (__lw->IsRunning())
			Thread::Sleep(1000);

		delete __lw;
	}
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
	String statement;

	if (__db->BeginTransaction() != E_SUCCESS)
		return false;

	statement.Format(1000, L"INSERT INTO %S (%S, %S, %S, %S, %S, %S) VALUES (?, ?, ?, ?, ?, ?)", TABLE_NAME, COLUMN_LESSON, COLUMN_LERN, COLUMN_NATIVE, COLUMN_LWEIGHT,
			COLUMN_NWEIGHT, COLUMN_USER_CHANGE);

	DbStatement * pStmt = __db->CreateStatementN(statement);

	pStmt->BindInt(0, word.__lesson);
	pStmt->BindString(1, word.__lern);
	pStmt->BindString(2, word.__native);
	pStmt->BindInt(3, word.__lweight);
	pStmt->BindInt(4, word.__nweight);
	pStmt->BindInt(5, 0);

	DbEnumerator * pEnum = __db->ExecuteStatementN(*pStmt);

	__db->CommitTransaction();

	delete pEnum;
	delete pStmt;

	AppLogDebug("word: %S - %S", word.__lern.GetPointer(), word.__native.GetPointer());
	return true;
}

void WordCtrl::CreateLessonWorker()
{
	// delete and create new LessonWorker
	__lw = new LessonWorker();
	__lw->Construct();
	__lw->SetLessonWorkerLissener(this);
}

bool WordCtrl::AddLesson(const int lesson, bool remove)
{
	bool createnew = false;

	if (!__lw)
	{
		CreateLessonWorker();
		createnew = true;
	}
	else
	{
		// set wait because, the __lw
		// can be on end of add/removing cycle
		// set wait on this cycle for try GetLessonFromList
		__lw->StartWait();
	}

	// the __lw is finished yet
	// you can create new therad
	// because old thread isn't abble to start again
	if (!createnew && !__lw->IsRunning())
	{
		__lw->StopWait();
		delete __lw;
		__lw = null;

		CreateLessonWorker();
		createnew = true;
	}

	// add/remove lesson at lesson
	__lw->AddLesson(lesson, remove);

	// it was create new start new thread
	// otherwise call StopWait -> continue cycle in Run
	if (createnew)
		__lw->Start();
	else __lw->StopWait();

	return true;
}

void WordCtrl::SetLessonWorkerListener(ILessonWorkerLissener *ilwl)
{
	__lwLissener = ilwl;

}

void WordCtrl::OnLessonTask(const int lesson)
{
	if (__lwLissener)
		__lwLissener->OnLessonTask(lesson);
}

bool WordCtrl::DeleteLesson(const int lesson)
{
	String statement;

	if (__db->BeginTransaction() != E_SUCCESS)
		return false;

	statement.Format(1000, L"DELETE FROM %S WHERE %S = ?", TABLE_NAME, COLUMN_LESSON);

	DbStatement * pStmt = __db->CreateStatementN(statement);

	pStmt->BindInt(0, lesson);

	DbEnumerator * pEnum = __db->ExecuteStatementN(*pStmt);

	__db->CommitTransaction();

	delete pEnum;
	delete pStmt;

	AppLog("Delete lesson: %d", lesson);
	return true;
}
